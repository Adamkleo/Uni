#include <stdio.h>
#include <netdb.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "lines.h"

int  main(int argc, char **argv)  // en argv[1] == servidor 
{
  // Descriptor for client socket
  int sd;
  // Struct to store address of server in binary
  struct sockaddr_in server_addr;
  // hostent struct that will contain the details of the host
  struct hostent *hp;
  // operands and result
  int32_t a, b, res;
  // oeprator
	char op;
  // Error store
	int err;

  if (argc != 2){
    printf("Uso: cliente <direccion_servidor> \n");
    return(0);
  }

  // Initialize socket
  sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		printf("Error en socket\n");
		return -1;
	}

  // Clear enough space in memory for server address struct
	bzero((char *)&server_addr, sizeof(server_addr));

  // get info of host
  hp = gethostbyname (argv[1]);
	if (hp == NULL) {
		printf("Error en gethostbyname\n");
		return -1;
	}

  // Write the server address to the server struct
  memcpy(&(server_addr.sin_addr), hp->h_addr, hp->h_length);
  server_addr.sin_family  = AF_INET;
  // Set port but convert to network byte order
  server_addr.sin_port    = htons(4200);
   	
	// Connection
  err = connect(sd, (struct sockaddr *) &server_addr,  sizeof(server_addr));
	if (err == -1) {
		printf("Error en connect\n");
		return -1;
	}
  
  // Convert the operands to network order so that they cant be sent and recieved properly
  a = htonl(5);
  b = htonl(2);
  op = 0; // sum operator

  err = sendMessage(sd, (char *) &op, sizeof(char));  // envía la operacion
	if (err == -1){
		printf("Error en envio\n");
		return -1;
	}
  err = sendMessage(sd, (char *) &a, sizeof(int32_t)); // envía a
	if (err == -1){
		printf("Error en envio\n");
		return -1;
	}
  err = sendMessage(sd, (char *) &b, sizeof(int32_t)); // envíab
	if (err == -1){
		printf("Error en envio\n");
		return -1;
	}

  err = recvMessage(sd, (char *) &res, sizeof(int32_t));     // recibe la respuesta
	if (err == -1){
		printf("Error en recepcion\n");
		return -1;
	}
	
  printf("Resultado es %d \n", ntohl(res));

  close (sd);
  return(0);
}
