#include "storage.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ------------- HASH TABLE ------------- */

// Create a new hash table
HashTable *createHashTable(int size) {
    // Allocate memory for the table
    HashTable *table = malloc(sizeof(HashTable));
    if (table == NULL)
        return NULL;

    // Allocate memory for the array of users
    table->size = size;
    table->users = malloc(sizeof(User *) * size);
    if (table->users == NULL) {
        free(table);
        return NULL;
    }
    // Initialize the array of users
    for (int i = 0; i < size; i++) {
        table->users[i] = NULL;
    }
    return table;
}

// Free the entire hash table
void freeHashTable(HashTable *table) {
    // Free each user in the table
    for (int i = 0; i < table->size; i++) {
        User *user = table->users[i];
        while (user != NULL) {
            User *temp = user;
            user = user->next;
            // Free the file list
            FileList *file = temp->files;
            while (file != NULL) {
                FileList *tempFile = file;
                file = file->next;
                free(tempFile);
            }
            free(temp);
        }
    }
    free(table->users);
    free(table);
}

// Hash function for a string
unsigned int hash(const char *key, int table_size) {
    // djb2 hash function
    unsigned long int hashval = 0;
    int i = 0;
    // Convert our string to an integer
    while (hashval < ULONG_MAX && i < strlen(key)) {
        hashval = hashval << 8;
        hashval += key[i];
        i++;
    }
    // Return the hash value mod the table size so that it's within range
    return hashval % table_size;
}

// Print the contents of the hash table (for debugging)
void printHashTable(HashTable *table) {
    // Iterate over each user in the table
    for (int i = 0; i < table->size; i++) {
        User *user = table->users[i];
        while (user != NULL) {
            // Print the user's information
            printf("User: %s\n", user->username);
            FileList *file = user->files;
            while (file != NULL) {
                // Print the user's files
                printf("  File: %-20s Description: %s\n", file->filename,
                       file->description);
                file = file->next;
            }
            user = user->next;
        }
    }
}

/* ------------- USER RELATED ------------- */

// Insert a user into the hash table
User *insertUser(HashTable *table, const char *username) {
    // Hash the username to get the index
    unsigned int index = hash(username, table->size);
    User *newUser = malloc(sizeof(User));
    if (newUser == NULL) {
        return NULL;
    }
    // Initialize the user's information
    strcpy(newUser->username, username);
    newUser->files = NULL;
    newUser->next = table->users[index];
    newUser->connection_status = NOT_CONNECTED;
    table->users[index] = newUser;
    return newUser;
}

// Delete a user from the hash table
int deleteUser(HashTable *table, const char *username) {
    // Hash the username to get the index
    unsigned int index = hash(username, table->size);
    User *user = table->users[index];
    User *prev = NULL;
    // Iterate over the list of users at the index
    while (user != NULL) {
        if (strcmp(user->username, username) == 0) {
            if (prev != NULL) {
                prev->next = user->next;
            } else {
                table->users[index] = user->next;
            }
            // Free the file list
            FileList *file = user->files;
            while (file != NULL) {
                FileList *temp = file;
                file = file->next;
                free(temp);
            }
            // Free the user
            free(user);
            return 0; // Success
        }
        // Move to the next user
        prev = user;
        user = user->next;
    }
    return 1; // User not found
}


User *findUser(HashTable *table, const char *username) {
    // Hash the username to get the index
    unsigned int index = hash(username, table->size);
    // Iterate over the list of users at the index
    User *user = table->users[index];
    // Search for the user with the given username
    while (user != NULL) {
        if (strcmp(user->username, username) == 0) {
            return user;
        }
        user = user->next;
    }
    return NULL;
}

/* ------------- FILE RELATED ------------- */

// Add a file to a user's list
FileList *addFileToUser(User *user, const char *filename,
                        const char *description) {
    // Allocate memory for the new file node
    FileList *newFile = malloc(sizeof(FileList));
    if (newFile == NULL)
        return NULL;

    // Initialize the file information
    strcpy(newFile->filename, filename);
    strcpy(newFile->description, description);
    // Add the file to the user's list
    newFile->next = user->files;
    user->files = newFile;
    return newFile;
}

// Delete a file from a user's file list
void deleteFileFromUser(User *user, const char *filename) {
    if (user == NULL || filename == NULL) {
        return; // Nothing to delete if user or filename is NULL
    }

    // Search for the file in the user's list
    FileList *current = user->files;
    FileList *prev = NULL;

    // Iterate over the list of files
    while (current != NULL) {
        if (strcmp(current->filename, filename) == 0) {
            if (prev != NULL) {
                prev->next = current->next; // Bypass the current node
            } else {
                user->files = current->next; // Update the head if it's the first node
            }
            free(current); // Free the memory allocated for the current file node
            return;
        }
        prev = current;
        current = current->next;
    }
}

int fileExists(User *user, const char *filename) {
    // Search for the file in the user's list
    FileList *file = user->files;
    // Iterate over the list of files
    while (file != NULL) {
        if (strcmp(file->filename, filename) == 0) {
            return FILE_FOUND; // File exists
        }
        file = file->next;
    }
    return FILE_NOT_FOUND; // File does not exist
}
