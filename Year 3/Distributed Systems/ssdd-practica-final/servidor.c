#include "operations.h"
#include "storage.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include "rpc_message.h"
char *ip_server;
pthread_mutex_t mutex_ejecucion;

void sigint_handler(int sig)
{
    printf("\nCaught signal %d\n", sig);
    exit(0); // Exit con status 0
}

void send_result(int client_socket, int res)
{
    char res_char = '0' + res; // Convierte 0, 1, 2 a '0', '1', '2'
    send(client_socket, &res_char, 1, 0);
    send(client_socket, "\0", 1, 0);
}

int send_string(int sockfd, const char *str)
{
    size_t len = strlen(str) + 1;                   // Incluir null terminator en la len
    ssize_t bytes_sent = send(sockfd, str, len, 0); // Enviar la string

    if (bytes_sent == -1)
    {
        perror("send failed");
        return -1;
    }
    // Comprobar si se ha enviado la string completa
    return (int)bytes_sent;
}

void ces(int result, const char *errmsg)
{
    if (result < 0)
    {
        perror(errmsg);
        exit(EXIT_FAILURE);
    }
}

// Función para iniciar el socket del server
int setup_server(int port)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    ces(server_socket, "Error creating socket");

    // Estructura de la dirección
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(port);

    // Enlazamos el socket con la address
    ces(bind(server_socket, (struct sockaddr *)&server_addr,
             sizeof(server_addr)),
        "Bind failed");
    ces(listen(server_socket, 10), "Listen failed");
    ip_server= inet_ntoa(server_addr.sin_addr);
    printf("s> init server %s:%d\ns>\n", ip_server, port);

    return server_socket;
}

typedef struct
{
    int client_socket;
    HashTable *userTable;
} ClientData;

// Función multihilo para gestionar requests de clientes
void *handle_client(void *arg)
{
    pthread_mutex_lock(&mutex_ejecucion);
    // // Sacamos client socket y la tabla de usuarios del argumento
    ClientData *data = (ClientData *)arg;
    int client_socket = data->client_socket;
    HashTable *userTable = data->userTable;
    CLIENT *clnt;
    enum clnt_stat retval_1;
    clnt = clnt_create(ip_server, SERVER_OPERATION, SERVER_OPERATION_VERS, "tcp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(ip_server);
        pthread_mutex_unlock(&mutex_ejecucion);
        return NULL;
    }
    free(arg);
    int result_rpc;
    char buffer[1024] = {0};
    int read_size = recv(client_socket, buffer, sizeof(buffer) - 1, 0);
    if (read_size < 0)
    {
        perror("Recv failed");
        close(client_socket);
        pthread_mutex_unlock(&mutex_ejecucion);
        return NULL;
    }

    // Sacamos dirección IP y puerto del cliente
    struct sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    if (getpeername(client_socket, (struct sockaddr *)&client_addr,
                    &client_addr_len) == -1)
    {
        perror("getpeername failed");
        close(client_socket);
        pthread_mutex_unlock(&mutex_ejecucion);
        return NULL;
    }
    
    // Convertir dirección IP a string
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(client_addr.sin_addr), client_ip, INET_ADDRSTRLEN);
    int client_port = ntohs(client_addr.sin_port);

    // Parsing de la operación,datetime y username del buffer
    const char *operation = buffer;
    const char *datetime = operation + strlen(operation) + 1;
    const char *username = datetime + strlen(datetime) + 1;

    PrintArgs struct_args;
    int res = -1;
    int ignore = 0;

    // Handle request
    if (strcmp(operation, "REGISTER") == 0)
    {
        res = handle_register(username, userTable);
        send_result(client_socket, res);
    }
    else if (strcmp(operation, "UNREGISTER") == 0)
    {
        res = handle_unregister(username, userTable);
        send_result(client_socket, res);
    }
    else if (strcmp(operation, "CONNECT") == 0)
    {
        const char *client_listening_port = username + strlen(username) + 1;
        res = handle_connect(username, userTable, client_ip, client_port,
                             client_listening_port);
        send_result(client_socket, res);
    }
    else if (strcmp(operation, "DISCONNECT") == 0)
    {
        res = handle_disconnect(username, userTable);
        send_result(client_socket, res);
    }
    else if (strcmp(operation, "PUBLISH") == 0)
    {
        const char *fileName = username + strlen(username) + 1;
        strcpy(struct_args.file, fileName);
        const char *description = fileName + strlen(fileName) + 1;
        res = handle_publish(username, fileName, description, userTable);
        send_result(client_socket, res);
    }
    else if (strcmp(operation, "DELETE") == 0)
    {
        const char *fileName = username + strlen(username) + 1;
        strcpy(struct_args.file, fileName);
        res = handle_delete(username, fileName, userTable);
        send_result(client_socket, res);
    }
    else if (strcmp(operation, "LIST_USERS") == 0)
    {
        char *output;
        output = handle_list_users(username, userTable, &res);
        send_result(client_socket, res);
        if (output != NULL)
        {
            send_string(client_socket, output);
            free(output);
        }
    }
    else if (strcmp(operation, "LIST_CONTENT") == 0)
    {
        char *output;
        const char *userWithFiles = username + strlen(username) + 1;
        output = handle_list_content(username, userTable, userWithFiles, &res);
        send_result(client_socket, res);

        if (output != NULL)
        {
            send_string(client_socket, output);
            free(output);
        }
    }
    else if (strcmp(operation, "UPDATE_USERS") == 0)
    {
        ignore = 1;
        const char *listening_port = username + strlen(username) + 1;
        handle_update_users(username, userTable, listening_port);
    }

    // Print de la operación
    if (ignore == 0)
    {
        printf("s> OPERATION FROM %s\n", username);
    }

    close(client_socket);
    strcpy(struct_args.date, datetime);
    strcpy(struct_args.operation, operation);
    strcpy(struct_args.username, username);
    retval_1 = print_1(struct_args, &result_rpc, clnt);
    if (retval_1 != RPC_SUCCESS)
    {
        clnt_perror(clnt, "RPC call failed");
        pthread_mutex_unlock(&mutex_ejecucion);
        return NULL;
    }

    clnt_destroy(clnt);
    pthread_mutex_unlock(&mutex_ejecucion);
    return NULL;
    
}

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: ./servidor <PORT>\n");
        return EXIT_FAILURE;
    }

    // Creamos el signal handler
    if (signal(SIGINT, sigint_handler) == SIG_ERR)
    {
        perror("Can't catch SIGINT");
        return 1;
    }

    // Inicializamos hashTable
    HashTable *userTable = createHashTable(INITIAL_SIZE);
    if (!userTable)
    {
        fprintf(stderr, "Failed to create user table\n");
        return EXIT_FAILURE;
    }
    //Se inicia el mutex para las requests del cliente
    pthread_mutex_init(&mutex_ejecucion,NULL);
    // Creación de server socket
    int server_socket = setup_server(atoi(argv[1]));
    // Aceptar conexiones de clientes
    struct sockaddr_in client_addr;
    socklen_t addr_size = sizeof(client_addr);

    while (1)
    {
        // Aceptar una nueva conexión
        ClientData *clientData = malloc(sizeof(ClientData));
        if (clientData == NULL)
        {
            perror("Failed to allocate memory for client data");
            continue;
        }
        // Aceptar la conexión del cliente
        clientData->client_socket =
            accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
        ces(clientData->client_socket, "Accept failed");

        // Pasar la userTable al thread
        clientData->userTable = userTable; // Conseguimos userTable para el thread

        // Creamos un nuevo thread para la request actual
        pthread_t thread;
        if (pthread_create(&thread, NULL, handle_client, (void *)clientData) !=
            0)
        {
            perror("Error creating thread");
            free(clientData);
        }
        else
        {
            pthread_detach(thread);
        }
    }

    // Cleanup
    freeHashTable(userTable);
    close(server_socket);
    pthread_mutex_destroy(&mutex_ejecucion);
    return 0;
}
