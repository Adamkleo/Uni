#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include "lines.h"

#define MAX_LINE 	256

int main(int argc, char *argv[])
{

  int sd;
  struct sockaddr_in server_addr;
  struct hostent *hp;
  
  if (argc != 3) {
    printf("Usage: client <serverAddress> <serverPort>\n");
    exit(0);
  }

	// the socket is create
  sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sd < 0) {
    perror("Error in socket");
    exit(1);
  }
	
  // Obtain Server address 
  bzero((char *)&server_addr, sizeof(server_addr));
  hp = gethostbyname (argv[1]);
  if (hp == NULL) {
    perror("Error en gethostbyname");
    exit(1);
  }

	memcpy (&(server_addr.sin_addr), hp->h_addr, hp->h_length);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[2]));

	// Complete.....
	// First: establish the connection

  if (connect(sd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == -1) {
    printf("Error in connect()!\n");
    return -1;
  }


  char buffer[MAX_LINE];
  int err = 0;
  int n;
  printf("Type 'EXIT' to quit!\n");

  while (1) {
  
    printf("Enter text: ");
    fflush(stdout);

    n = readLine(0,  buffer, MAX_LINE - 1);
    if (n < 0) {
      printf("Error or end of file!\n");
      return -1;
    }


    err = sendMessage(sd, (char *) buffer, strlen(buffer) + 1);
    if (err == -1) {
      printf("Error in send!\n");
      return -1;
    }

    
    if (strcmp(buffer, "EXIT") == 0) {
      printf("Exiting!\n");
      break;
    }


    memset(buffer, 0, MAX_LINE);

    err = recvMessage(sd, (char *) &buffer, MAX_LINE);
    if (err == -1) {
      printf("Error in response!\n");
      return -1;
    } 

    printf("Message recieved: %s\n", buffer);
    
    memset(buffer, 0, MAX_LINE);
  }
  close (sd);
  return(0);
}


// ./client localhost 2000
