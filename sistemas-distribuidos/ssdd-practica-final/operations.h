#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "storage.h"


int handle_register(const char *username, HashTable *userTable);

int handle_unregister(const char *username, HashTable *userTable);

int handle_connect(const char *username, HashTable *userTable, const char *ip_address, int port,const char* client_port);

int handle_disconnect(const char *username, HashTable *userTable);

int handle_publish(const char *username, const char *filename, const char *description, HashTable *userTable);

int handle_delete(const char *username, const char *filename, HashTable *userTable);

char *handle_list_users(const char *username, HashTable *userTable, int *res);

char *handle_list_content(const char *username, HashTable *userTable, const char *userWithFiles, int *res);

void handle_update_users(const char *username, HashTable *userTable, const char *listening_port);
#endif

