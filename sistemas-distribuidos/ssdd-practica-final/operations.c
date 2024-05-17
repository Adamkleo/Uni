#include "storage.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void toLowerCase(char *str) {
    if (str) {
        while (*str) {
            *str = tolower((unsigned char)*str);
            str++;
        }
    }
}

int handle_register(const char *username, HashTable *userTable) {
    char username_lower[256]; // assuming username length limit is 255
    strcpy(username_lower, username);
    toLowerCase(username_lower);

    if (findUser(userTable, username_lower) != NULL)
        return 1; // Username already in use

    if (insertUser(userTable, username_lower) == NULL)
        return 2; // Insertion failed

    return 0; // Success
}

int handle_unregister(const char *username, HashTable *userTable) {
    char username_lower[256];
    strcpy(username_lower, username);
    toLowerCase(username_lower);

    if (findUser(userTable, username_lower) == NULL)
        return 1; // Username not found

    if (deleteUser(userTable, username_lower) == 1)
        return 2; // Deletion failed

    return 0; // Deleted user
}

int handle_connect(const char *username, HashTable *userTable,
                   const char *ip_address, int port,const char* client_port) {
    char username_lower[256];
    strcpy(username_lower, username);
    toLowerCase(username_lower);

    // Check if the user is registered
    User *user = findUser(userTable, username_lower);
    if (user == NULL)
        return 1; // Username not found

    // Check if the user is already connected
    if (user->connection_status == CONNECTED) {
        return 2; // User already connected
    }

    // Mark the user as connected
    user->connection_status = CONNECTED;
    user->port = port;
    user->client_listening_port=atoi(client_port);
    strcpy(user->ip_address, ip_address);

    return 0; // Success, user is now connected
}

int handle_disconnect(const char *username, HashTable *userTable) {
    char username_lower[256];
    strcpy(username_lower, username);
    toLowerCase(username_lower);

    // Check if the user is registered
    User *user = findUser(userTable, username_lower);
    if (user == NULL)
        return 1; // Username not found

    if (user->connection_status == NOT_CONNECTED)
        return 2; // User not connected

    // Mark the user as disconnected
    if (user->connection_status == CONNECTED) {
        user->connection_status = NOT_CONNECTED;
        return 0; // Success, user is now disconnected
    }

    return 3; // Unknown error
}

int handle_publish(const char *username, const char *filename,
                   const char *description, HashTable *userTable) {
    char username_lower[256];
    strcpy(username_lower, username);
    toLowerCase(username_lower);

    User *user = findUser(userTable, username_lower);
    if (user == NULL)
        return 1; // Username not found

    if (user->connection_status == NOT_CONNECTED)
        return 2; // User not connected

    if (fileExists(user, filename) == FILE_FOUND)
        return 3; // File already exists

    if (addFileToUser(user, filename, description) == NULL)
        return 4; // File addition failed

    return 0; // Success
}

int handle_delete(const char *username, const char *filename,
                  HashTable *userTable) {
    char username_lower[256];
    strcpy(username_lower, username);
    toLowerCase(username_lower);

    User *user = findUser(userTable, username_lower);
    if (user == NULL)
        return 1; // Username not found

    if (user->connection_status == NOT_CONNECTED)
        return 2; // User not connected

    if (fileExists(user, filename) == FILE_NOT_FOUND)
        return 3; // File not found

    deleteFileFromUser(user, filename);
    return 0; // Success
}



char *handle_list_users(const char *username, HashTable *userTable, int *res) {
    // Assuming each user info might take up to 100 characters, including spaces and newlines
    int estimated_size = userTable->size * 100;
    char *result = malloc(estimated_size);
    if (result == NULL) {
        *res = -1; // Memory allocation failure
        return NULL;
    }
    result[0] = '\0'; // Start with an empty string
    char username_lower[256];
    strcpy(username_lower, username);
    toLowerCase(username_lower);
    User *user = findUser(userTable, username_lower);
    if (user == NULL) {
        *res = 1; // Username not found
        free(result);
        return NULL;
    }
    if (user->connection_status != CONNECTED) {
        *res = 2; // User not connected
        free(result);
        return NULL;
    }
    char user_info[300];
    for (int i = 0; i < userTable->size; i++) {
        User *user = userTable->users[i];
        while (user != NULL) {
            if (user->connection_status == CONNECTED) {
                snprintf(user_info, sizeof(user_info), "%-10s  %-5s  %-5d\n", user->username, user->ip_address, user->client_listening_port);
                strcat(result, user_info);
            }
            user = user->next;
        }
    }
    *res = 0; // Success
    return result;
}

char *handle_list_content(const char *username, HashTable *userTable,
                          const char *userWithFiles, int *res) {
    // Assuming each file info might take up to 300 characters, including spaces and newlines
    int estimated_size = userTable->size * 300;
    char *result = malloc(estimated_size);
    if (result == NULL) {
        *res = 4; // Memory allocation failure
        return NULL;
    }
    result[0] = '\0'; // Start with an empty string
    char username_lower[256];
    strcpy(username_lower, username);
    toLowerCase(username_lower);
    User *user = findUser(userTable, username_lower);
    if (user == NULL) {
        *res = 1; // Username not found
        free(result);
        return NULL;
    }
    if (user->connection_status == NOT_CONNECTED) {
        *res = 2; // User not connected
        free(result);
        return NULL;
    }
    char userWithFiles_lower[256];
    strcpy(userWithFiles_lower, userWithFiles);
    toLowerCase(userWithFiles_lower);
    User *userWithFilesNode = findUser(userTable, userWithFiles_lower);
    if (userWithFilesNode == NULL) {
        *res = 3; // User with files not found
        free(result);
        return NULL;
    }

    FileList *file = userWithFilesNode->files;
    while (file != NULL) {
        snprintf(result + strlen(result), estimated_size - strlen(result), "    %-20s  %s\n", file->filename, file->description);
        file = file->next;
    }
    *res = 0; // Success
    return result;
}


void handle_update_users(const char *username, HashTable *userTable, const char *listening_port) {
    char username_lower[256];
    strcpy(username_lower, username);
    toLowerCase(username_lower);

    User *user = findUser(userTable, username_lower);
    if (user == NULL)
        return; // Username not found

    if (user->connection_status == NOT_CONNECTED)
        return; // User not connected

    user->client_listening_port = atoi(listening_port);
}