#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "message.h"

void serialize_message(const Message* msg, unsigned char* buffer) {
    int offset = 0;
    *(int*)(buffer + offset) = htonl(msg->operation);
    offset += sizeof(int);
    *(int*)(buffer + offset) = htonl(msg->status);
    offset += sizeof(int);
    *(int*)(buffer + offset) = htonl(msg->key);
    offset += sizeof(int);

    strncpy((char*)buffer + offset, msg->value1, 256);
    offset += 256;

    *(int*)(buffer + offset) = htonl(msg->N_value2);
    offset += sizeof(int);

    for (int i = 0; i < msg->N_value2; i++) {
        *(double*)(buffer + offset) = msg->value2[i];
        offset += sizeof(double);
    }
}

void deserialize_message(const unsigned char* buffer, Message* msg) {
    int offset = 0;
    msg->operation = ntohl(*(int*)(buffer + offset));
    offset += sizeof(int);
    msg->status = ntohl(*(int*)(buffer + offset));
    offset += sizeof(int);
    msg->key = ntohl(*(int*)(buffer + offset));
    offset += sizeof(int);

    strncpy(msg->value1, (char*)buffer + offset, 256);
    offset += 256;

    msg->N_value2 = ntohl(*(int*)(buffer + offset));
    offset += sizeof(int);

    for (int i = 0; i < msg->N_value2; i++) {
        msg->value2[i] = *(double*)(buffer + offset);
        offset += sizeof(double);
    }
}

int send_receive(Message *msg) {
    int sd;
    struct sockaddr_in server_addr;
    struct hostent *server;
    char *serverIP, *serverPortStr;
    int serverPort;
    serverIP = getenv("IP_TUPLAS");
    serverPortStr = getenv("PORT_TUPLAS");
    if (!serverIP || !serverPortStr) {
        fprintf(stderr, "Server IP or Port not set in environment variables.\n");
        return ERROR;
    }
    serverPort = atoi(serverPortStr);

    sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd < 0) {
        perror("Error creating socket");
        return ERROR;
    }

    server = gethostbyname(serverIP);
    if (!server) {
        fprintf(stderr, "Error resolving host %s\n", serverIP);
        close(sd);
        return ERROR;
    }

    bzero((char *)&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&server_addr.sin_addr.s_addr, server->h_length);
    server_addr.sin_port = htons(serverPort);

    if (connect(sd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error connecting to server");
        close(sd);
        return ERROR;
    }

    unsigned char buffer[sizeof(Message) + 256 + msg->N_value2 * sizeof(double)]; // Adjusted for dynamic content
    serialize_message(msg, buffer);

    if (write(sd, buffer, sizeof(buffer)) < 0) {
        perror("Error sending message to server");
        close(sd);
        return ERROR;
    }

    if (read(sd, buffer, sizeof(buffer)) < 0) {
        perror("Error receiving response from server");
        close(sd);
        return ERROR;
    }

    deserialize_message(buffer, msg);

    close(sd);
    return SUCCESS;
}
