#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "claves.h"

int main() {
    int key = 1; 
    char value1[256] = "Example String"; 
    int N_value2 = 3; 
    double V_value2[32] = {1.1, 2.2, 3.3}; 

    printf("Setting value for key: %d\n", key);
    if (set_value(key, value1, N_value2, V_value2) == 0) {
        printf("Set value operation successful.\n");
    } else {
        fprintf(stderr, "Set value operation failed.\n");
        return EXIT_FAILURE; 
    }

    printf("Getting value for key: %d\n", key);
    if (get_value(key, value1, &N_value2, V_value2) == 0) {
        printf("Get value operation successful.\n");
        printf("Retrieved Value1: %s\n", value1);
        printf("Retrieved N_value2: %d\n", N_value2);
        printf("Retrieved Value2: ");
        for (int i = 0; i < N_value2; i++) {
            printf("%f ", V_value2[i]);
        }
        printf("\n");
    } else {
        fprintf(stderr, "Get value operation failed or key does not exist.\n");
    }

    // Modify the value associated with the key
    printf("Modifying value for key: %d\n", key);
    strcpy(value1, "Modified String");
    N_value2 = 2; 
    double modifiedV_value2[32] = {4.4, 5.5}; 
    if (modify_value(key, value1, N_value2, modifiedV_value2) == 0) {
        printf("Modify value operation successful.\n");
    } else {
        fprintf(stderr, "Modify value operation failed.\n");
    }

    // Check if key exists
    printf("Checking existence for key: %d\n", key);
    if (exist(key) == 1) {
        printf("Key exists.\n");
    } else if (exist(key) == 0) {
        printf("Key does not exist.\n");
    } else {
        fprintf(stderr, "Exist operation failed.\n");
    }

    // Delete the key
    printf("Deleting key: %d\n", key);
    if (delete_key(key) == 0) {
        printf("Delete key operation successful.\n");
    } else {
        fprintf(stderr, "Delete key operation failed.\n");
    }

    // Try to get value for the deleted key
    memset(value1, 0, sizeof(value1)); // Clear out value1 buffer
    printf("Attempting to get value for the deleted key: %d\n", key);
    if (get_value(key, value1, &N_value2, V_value2) == 0) {
        printf("Unexpected success in get_value operation for a deleted key.\n");
    } else {
        printf("Correctly failed to get value for a deleted key.\n");
    }

    int res = init();
    printf("Result of init: %d\n", res);

    return EXIT_SUCCESS;
}

