#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include "message.h"

typedef struct
{
  int key;
  char value1[256];
  int N;
  double *value2;
} KeyValue;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int init_operation();
int set_value_operation(int key, char *value1, int N_value2, double *V_value_2);
int get_value_operation(int key, char *value1, int *N_value2, double *V_value_2);
int modify_value_operation(int key, char *value1, int N_value2, double *V_value2);
int delete_key_operation(int key);
int exists_operation(int key);
int get_index(int key);

void *handle_client(void *arg) {
    pthread_mutex_lock(&lock);

    int sc = *((int *)arg);
    free(arg);

    unsigned char buffer[sizeof(Message) + 256 + 32 * sizeof(double)]; // Adjust buffer size as needed
    bzero(buffer, sizeof(buffer));

    int read_size = read(sc, buffer, sizeof(buffer));
    if (read_size > 0) {
        Message msg;
        deserialize_message(buffer, &msg); // Deserialize the received data into msg

        switch (msg.operation) {
        case SET_VALUE:
            msg.status = set_value_operation(msg.key, msg.value1, msg.N_value2, msg.value2);
            break;
        case GET_VALUE:
        {
            double tempValue2[32];
            msg.status = get_value_operation(msg.key, msg.value1, &msg.N_value2, tempValue2);
            if (msg.status == 0) {
                memcpy(msg.value2, tempValue2, msg.N_value2 * sizeof(double));
            }
            break;
        }
        case MODIFY_VALUE:
            msg.status = modify_value_operation(msg.key, msg.value1, msg.N_value2, msg.value2);
            break;
        case DELETE_KEY:
            msg.status = delete_key_operation(msg.key);
            break;
        case EXISTS:
            msg.status = exists_operation(msg.key);
            break;
        case INIT:
            msg.status = init_operation();
            break;
        default:
            msg.status = ERROR;
            break;
        }

        // Serialize the response msg before sending it back
        bzero(buffer, sizeof(buffer));
        serialize_message(&msg, buffer);
        write(sc, buffer, sizeof(buffer));
    } else if (read_size == 0) {
        printf("Client disconnected\n");
    } else {
        perror("Error reading from socket");
    }
    close(sc);
    pthread_mutex_unlock(&lock);
    return NULL;
}


void insertKeyValue(KeyValue **array, int *size, int *capacity, KeyValue newKeyValue)
{
  if (*size >= *capacity)
  {
    *capacity *= 2;
    *array = realloc(*array, (*capacity) * sizeof(KeyValue));
    if (*array == NULL)
    {
      perror("Failed to resize array!");
      exit(EXIT_FAILURE);
    }
  }
  (*array)[*size] = newKeyValue;
  (*size)++;

}

void freeArray(KeyValue *array, int size)
{
  for (int i = 0; i < size; i++)
  {
    if (array[i].value2 != NULL)
    {
      free(array[i].value2);
    }
  }
  free(array);
}

KeyValue *array;
int size = 0;
int capacity = 1;

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    printf("Use ./servidor {PORT}\n");
    pthread_mutex_destroy(&lock);
    return EXIT_FAILURE;
  }

  int sd, sc;
  int val;
  int err;
  struct sockaddr_in server_addr, client_addr;

  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sd < 0)
  {
    perror("Error in socket!");
    close(sd);
    pthread_mutex_destroy(&lock);

    return EXIT_FAILURE;
  }

  val = 1;
  err = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&val, sizeof(int));
  if (err < 0)
  {
    perror("Error in socket options!");
    close(sd);
    pthread_mutex_destroy(&lock);
    return EXIT_FAILURE;
  }

  bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(atoi(argv[1]));

  err = bind(sd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
  if (err == -1)
  {
    printf("Error in bind!\n");
    close(sd);
    pthread_mutex_destroy(&lock);
    return EXIT_FAILURE;
  }

  err = listen(sd, SOMAXCONN);
  if (err == -1)
  {
    printf("Error in listen!\n");
    close(sd);
    pthread_mutex_destroy(&lock);
    return EXIT_FAILURE;
  }

  int client_addr_size = sizeof(client_addr);

  array = malloc(1 * sizeof(KeyValue));
  if (array == NULL)
  {
    perror("Failed to allocate array");
    pthread_mutex_destroy(&lock);
    close(sd);
    return EXIT_FAILURE;
  }

  while (1)
  {
    printf("Waiting for a connection!\n");

    sc = accept(sd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_size);
    if (sc == -1)
    {
      perror("Error in accept");
      
      continue;
    }

    printf("Connection accepted from IP: %s, Port: %d\n",
           inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    int *new_sc = malloc(sizeof(int));
    *new_sc = sc;

    pthread_t thread;
    if (pthread_create(&thread, NULL, handle_client, (void *)new_sc) == -1)
    {
      perror("Error creating thread!");
      close(sc);
      continue;
    }
    pthread_detach(thread);
  }

  pthread_mutex_destroy(&lock);
  close(sd);
  freeArray(array, size);

  return EXIT_SUCCESS;
}

int exists_operation(int key)
{
  int i;
  for (i = 0; i < size; i++)
  {
    if (array[i].key == key)
    {
      return 1;
    }
  }
  return SUCCESS;
}

int set_value_operation(int key, char *value1, int N_value2, double *V_value_2)
{
  int keyExists = exists_operation(key);

  if (keyExists == 1)
  {
    printf("Key already exists!");
    return ERROR;
  }

  if (keyExists == -1)
  {
  }

  KeyValue elem;
  elem.key = key;
  elem.N = N_value2;
  elem.value2 = (double *)malloc(N_value2 * sizeof(double));
  if (elem.value2 == NULL)
  {
    perror("Failed to allocate value2!");
    return EXIT_FAILURE;
  }
  memcpy(elem.value2, V_value_2, N_value2 * sizeof(double));
  strcpy(elem.value1, value1);

  insertKeyValue(&array, &size, &capacity, elem);

  return SUCCESS;
}

int get_value_operation(int key, char *value1, int *n_value2, double *V_value_2)
{
  int index = get_index(key);
  if (index < 0)
  {
    perror("Key does not exist!");
    return ERROR;
  }

  strcpy(value1, array[index].value1);
  *n_value2 = array[index].N;
  memcpy(V_value_2, array[index].value2, array[index].N * sizeof(double));
  return SUCCESS;
}

int modify_value_operation(int key, char *value1, int N_value2, double *V_value2)
{
  int index = get_index(key);
  if (index < 0)
  {
    return ERROR;
  }

  if (array[index].value2 != NULL)
  {
    free(array[index].value2);
  }

  strcpy(array[index].value1, value1);

  array[index].N = N_value2;
  array[index].value2 = (double *)malloc(N_value2 * sizeof(double));
  if (array[index].value2 == NULL)
  {
    perror("Failed to allocate memory for value2");
    return ERROR;
  }
  memcpy(array[index].value2, V_value2, N_value2 * sizeof(double));

  return SUCCESS;
}

int delete_key_operation(int key)
{
  int index = get_index(key);
  if (index < 0)
  {
    return ERROR;
  }

  if (array[index].value2 != NULL)
  {
    free(array[index].value2);
    array[index].value2 = NULL;
  }

  for (int i = index; i < size - 1; i++)
  {
    array[i] = array[i + 1];
  }

  size--;

  return SUCCESS;
}

int get_index(int key)
{
  int i;
  for (i = 0; i < size; i++)
  {
    if (array[i].key == key)
    {
      return i;
    }
  }
  return ERROR;
}

int init_operation()
{

  for (int i = 0; i < size; i++)
  {
    if (array[i].value2 != NULL)
    {
      free(array[i].value2);
      array[i].value2 = NULL;
    }
  }

  free(array);
  array = NULL;

  size = 0;
  capacity = 1;

  array = malloc(capacity * sizeof(KeyValue));
  if (array == NULL)
  {
    perror("Failed to allocate array in init");
    return ERROR;
  }

  return SUCCESS;
}
