#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "lines.h"

#define MAX_LINE 256
#define ERROR_CODE -1

void* handle_client(void* arg);


int main(int argc, char *argv[])
{
  int sd, sc;
	int val;
	int err;
  struct sockaddr_in server_addr, client_addr;


  sd =  socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sd < 0) {
    perror("Error in socket");
    exit(1);
  }

  val = 1;
  err = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &val,
                   sizeof(int));
  if (err < 0) {
    perror("Error in opction");
    exit(1);
  }

	// Complete .....

  bzero((char *) &server_addr, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port = htons(2000);

  err = bind(sd, (const struct sockaddr *) &server_addr, sizeof(server_addr));

  if (err == -1) {
    printf("Error in bind!\n");
    return -1;
  }

  err = listen(sd, SOMAXCONN);
  if (err == -1) {
    printf("Error in listen!\n");
    return -1;
  }

  int size = sizeof(client_addr);

  while (1) {
    printf("Waiting for a connection!\n");

    sc = accept(sd, (struct sockaddr *) &client_addr, (socklen_t *) &size);


    printf("Connection accepted from IP: %s, Port: %d\n", 
           inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port));

    if (sc == -1) {
      printf("Error in accept!\n");
      return -1;
    }

    pthread_t thread;
    int* new_sc = malloc(sizeof(int));
    *new_sc = sc;
    
    if (pthread_create(&thread, NULL, handle_client, (void*) new_sc) == -1) {
      printf("Error creating thread!\n");
      return -1;
    }
  
    pthread_detach(thread);

  }

  close (sd);
  return(0);
}



void* handle_client(void* arg) {
  int err;
  int client_socket = *((int *) arg);
  char buffer[MAX_LINE];
  int n;

  while (1) {
    n = readLine(client_socket, buffer, MAX_LINE);
    if (n < 0) {
      printf("Error or end of file!\n");
      return (void*) ERROR_CODE;
    }
    
    if (strcmp(buffer, "EXIT") == 0) {
      break;
    }

    err = sendMessage(client_socket, (char *) buffer, MAX_LINE);
    if (err == -1) {
      printf("Error in send!\n");
      return (void*) ERROR_CODE;
    }
    
    memset(buffer, 0, MAX_LINE);
    }
  
  return (void*) EXIT_SUCCESS;
}






