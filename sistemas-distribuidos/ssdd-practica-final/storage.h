#ifndef STORAGE_H
#define STORAGE_H

#define INITIAL_SIZE 100
#define MAX_FILENAME 256
#define MAX_USERNAME 256
#define MAX_DESCRIPTION 256

#define ULONG_MAX 0xFFFFFFFFUL

#define CONNECTED 0
#define NOT_CONNECTED 1

#define FILE_FOUND 0
#define FILE_NOT_FOUND 1

// Node to store a list of file names
typedef struct FileList {
    char filename[MAX_FILENAME];
    char description[MAX_DESCRIPTION];
    struct FileList *next;
} FileList;

// Node to store user information
typedef struct User {
    char username[MAX_USERNAME];
    FileList *files;
    struct User *next;
    int connection_status;
    int port;
    char ip_address[16];
    int client_listening_port;
} User;

// Hash table structure
typedef struct HashTable {
    int size;
    User **users;
} HashTable;

// Function prototypes

/* ------------- HASH TABLE ------------- */
HashTable *createHashTable(int size);
void freeHashTable(HashTable *table);
unsigned int hash(const char *key, int table_size);
void printHashTable(HashTable *table);

/* ------------- USER RELATED ------------- */
User *insertUser(HashTable *table, const char *username);
int deleteUser(HashTable *table, const char *username);
User *findUser(HashTable *table, const char *username);

/* ------------- FILE RELATED ------------- */
FileList *addFileToUser(User *user, const char *filename,
                        const char *description);
void deleteFileFromUser(User *user, const char *filename);
int fileExists(User *user, const char *filename);

#endif
