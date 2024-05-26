#include <stdio.h>
#include <unistd.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "lines.h"

int main(int argc, char *argv[]){
  // structs to store the address of the server itself and tue client
  struct sockaddr_in server_addr,  client_addr;
	socklen_t size;
  int sd, sc;
  int val;
  char op;
  int32_t a, b, res;
	int err;

  // init server socket
  if ((sd = socket(AF_INET, SOCK_STREAM, 0))<0){
    printf ("SERVER: Error en el socket");
    return (0);
  }
  val = 1;
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *) &val, sizeof(int));

	bzero((char *)&server_addr, sizeof(server_addr));
  server_addr.sin_family      = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY;
  server_addr.sin_port        = htons(4200);

  // bind, or give, the socket the address of the server
  err = bind(sd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
	if (err == -1) {
		printf("Error en bind\n");
		return -1;
	}

  // listen to messages
  err = listen(sd, SOMAXCONN);
	if (err == -1) {
		printf("Error en listen\n");
		return -1;
	}

  size = sizeof(client_addr);

  while (1){
    printf("esperando conexion\n");
    // accept messages from the client, they are sent from the client to the servers socket
    // sd and the second parameter is the address of the socket of the client, third is its size
    sc = accept(sd, (struct sockaddr *)&client_addr, (socklen_t *)&size);

		if (sc == -1) {
			printf("Error en accept\n");
			return -1;
		}
    // print the accepted connection from clients ip and port but convert
    // the ip to ascii
    // the port to host format 
		printf("conexion aceptada de IP: %s   Puerto: %d\n", \ 
         inet_ntoa(client_addr.sin_addr), \
         ntohs(client_addr.sin_port));

  		err = recvMessage ( sc, (char *) &op, sizeof(char));   // recibe la operació
		if (err == -1) {
			printf("Error en recepcion\n");
			close(sc);
			continue;
		}
		err = recvMessage( sc, (char *) &a, sizeof(int32_t)); // recibe a
		if (err == -1) {
			printf("Error en recepcion\n");
			close(sc);
			continue;
		}
		err = recvMessage( sc, (char *) &b, sizeof(int32_t)); // recibe b
		if (err == -1) {
			printf("Error en recepcion\n");
			close(sc);
			continue;
		}
    
		a = ntohl(a);
		b = ntohl(b);

   		if (op == 0) // procesa la petición
      			res = a + b;
   		else
      			res = a - b;

		res = htonl(res);
   		err = sendMessage(sc, (char *)&res, sizeof(int32_t));  // envía el resultado
		if (err == -1) {
			printf("Error en envio\n");
			close(sc);
			continue;
		}

   		close(sc);                      // cierra la conexin (sc)
	}
	close (sd);

     	return(0);
} /*fin main */

