#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "claves.h"
#include "message.h"

int init()
{
    Message msg;

    // Prepare the message for the init operation
    bzero(&msg, sizeof(Message));
    msg.operation = INIT; // Assuming INIT is the operation code for initialization

    // Send the message and wait for a response
    if (send_receive(&msg) != SUCCESS)
    {
        fprintf(stderr, "Failed to send/receive the init message.\n");
        return ERROR;
    }

    return msg.status;
}

int set_value(int key, char *value1, int N_value2, double *V_value2)
{
    if (strlen(value1) > 255) { 
        perror("Value1 is too long.\n");
        return ERROR;
    }


    Message msg;

    // Prepare the message
    bzero(&msg, sizeof(Message));
    msg.operation = SET_VALUE; // Assuming you have defined operation codes
    msg.key = key;
    strncpy(msg.value1, value1, sizeof(msg.value1) - 1); // Safely copy string
    msg.value1[sizeof(msg.value1) - 1] = '\0';           // Ensure null-termination
    msg.N_value2 = N_value2;

    // Ensure N_value2 does not exceed the bounds of the msg.value2 array
    if (N_value2 < 0 || N_value2 > 32)
    {
        fprintf(stderr, "N_value2 is out of range.\n");
        return ERROR;
    }

    // Copy the value2 array into the message
    for (int i = 0; i < N_value2; ++i)
    {
        msg.value2[i] = V_value2[i];
    }

    // Send the message and wait for a response
    if (send_receive(&msg) != SUCCESS)
    {
        fprintf(stderr, "Failed to send/receive the message.\n");
        return ERROR;
    }

    return msg.status;
}

int get_value(int key, char *value1, int *N_value2, double *V_value2)
{

    if (strlen(value1) > 255) { 
        perror("Value1 is too long.\n");
        return ERROR;
    }

    Message msg;

    memset(&msg, 0, sizeof(msg));

    msg.operation = GET_VALUE; // Your operation code for get_value
    msg.key = key;

    int result = send_receive(&msg);
    if (result != SUCCESS)
    {
        fprintf(stderr, "Failed to communicate with the server.\n");
        return ERROR;
    }

    if (msg.status == SUCCESS)
    {
        strncpy(value1, msg.value1, 255); // Ensure not to overflow the buffer
        value1[255] = '\0';               // Ensure null-termination
        *N_value2 = msg.N_value2;
        memcpy(V_value2, msg.value2, (*N_value2) * sizeof(double));
    }
    else
    {
        return ERROR; // Indicate failure
    }

    return msg.status;
}

int modify_value(int key, char *value1, int N_value2, double *V_value2)
{

        if (strlen(value1) > 255) { 
        perror("Value1 is too long.\n");
        return ERROR;
    }
    Message msg;

    // Clear the message structure
    memset(&msg, 0, sizeof(msg));

    // Prepare the message
    msg.operation = MODIFY_VALUE; // The operation code for modify_value
    msg.key = key;
    strncpy(msg.value1, value1, sizeof(msg.value1) - 1); // Copy value1
    msg.value1[sizeof(msg.value1) - 1] = '\0';           // Ensure null-termination
    msg.N_value2 = N_value2;
    memcpy(msg.value2, V_value2, N_value2 * sizeof(double)); // Copy value2 array

    // Send the request and receive the response
    int result = send_receive(&msg);
    if (result != SUCCESS)
    {
        fprintf(stderr, "Failed to communicate with the server for modify operation.\n");
        return ERROR;
    }

    // Check response status
    return msg.status;
}

int delete_key(int key)
{
    Message msg;
    memset(&msg, 0, sizeof(msg));

    msg.operation = DELETE_KEY;
    msg.key = key;

    if (send_receive(&msg) != SUCCESS)
    {
        return ERROR;
    }

    return msg.status;
}

int exist(int key)
{
    Message msg;
    memset(&msg, 0, sizeof(msg));

    msg.operation = EXISTS;
    msg.key = key;

    if (send_receive(&msg) != SUCCESS)
    {
        return ERROR;
    }

    return msg.status;
}
