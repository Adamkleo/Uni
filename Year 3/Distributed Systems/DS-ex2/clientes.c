#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "claves.h"

void* client_operations(void* arg) {
    int key = *(int*)arg;
    char value1[256];
    snprintf(value1, sizeof(value1), "Example String from client %d", key);
    int N_value2 = 3;
    double V_value2[32] = {1.1, 2.2, 3.3};

    printf("Client %d: Setting value for key: %d\n", key, key);
    if (set_value(key, value1, N_value2, V_value2) != 0) {
        fprintf(stderr, "Client %d: Set value operation failed.\n", key);
        pthread_exit(NULL);
    }

    printf("Client %d: Getting value for key: %d\n", key, key);
    if (get_value(key, value1, &N_value2, V_value2) != 0) {
        fprintf(stderr, "Client %d: Get value operation failed or key does not exist.\n", key);
    }

    printf("Client %d: Modifying value for key: %d\n", key, key);
    snprintf(value1, sizeof(value1), "Modified String from client %d", key);
    N_value2 = 2;
    double modifiedV_value2[32] = {4.4, 5.5};
    if (modify_value(key, value1, N_value2, modifiedV_value2) != 0) {
        fprintf(stderr, "Client %d: Modify value operation failed.\n", key);
    }

    printf("Client %d: Deleting key: %d\n", key, key);
    if (delete_key(key) != 0) {
        fprintf(stderr, "Client %d: Delete key operation failed.\n", key);
    }

    pthread_exit(NULL);
}

int main(int argc, char** argv) {
    int client_count = 5; // Example: Creating 5 client threads
    pthread_t threads[client_count];
    int keys[client_count];

    for (int i = 0; i < client_count; i++) {
        keys[i] = i + 1; // Assign a unique key to each client
        if (pthread_create(&threads[i], NULL, client_operations, (void*)&keys[i]) != 0) {
            perror("Failed to create thread");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < client_count; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All client operations completed.\n");

    return EXIT_SUCCESS;
}

