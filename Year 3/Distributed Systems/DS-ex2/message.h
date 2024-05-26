// message.h
#ifndef MESSAGE_H
#define MESSAGE_H

// Operation codes
#define INIT        0
#define SET_VALUE   1
#define GET_VALUE   2
#define MODIFY_VALUE 3
#define DELETE_KEY  4
#define EXISTS      5

// Response status codes
#define SUCCESS     0
#define ERROR       -1
#define EXISTS_YES  1
#define EXISTS_NO   0

#include <stdint.h> // For fixed-width integer types

typedef struct {
    int operation;              // Operation code
    int status;                 // Response status code
    int key;                    // Key for the operation
    char value1[256];           // Value1: string of up to 255 chars + '\0'
    int N_value2;               // Number of elements in value2
    double value2[32];          // Value2: array of doubles
} Message;


void serialize_message(const Message* msg, unsigned char* buffer);

void deserialize_message(const unsigned char* buffer, Message* msg);

int send_receive(Message *msg);


#endif // MESSAGE_H

