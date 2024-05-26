#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char *argv[])
{
  /*
   * int gethostname(char *name, size_t namelen);
   * This function can be used to get the host name
   * name is a buffer to store the returned name
   * namelen is the length of the buffer
  */

  // Example of getting the name of the host or the executer
  char buff[256];
  int err;

  if (gethostname(buff, 256) == -1) {
    return -1;
  }
  
  printf("Executed in machine with name %s\n", buff);


  /*
   * char *inet_ntoa(struct in_addr in);
   * returns an ip address in decimal
   *
   * int inet_aton(const char *cp, struct in_addr *in);
   * gets an ip address in binary from a decimal address
   *
   * const char *inet_ntop(int domain, const void *addrptr, char *dst_str, size_t len);
   * returns an understandable ip address
   *
   * int inet_pton(int domain, const char *src_str, void *addrptr);
   * gets an ip address in binary from the understandable ip address
   *
   * These functions can be used to obtain addresses of a host and manage address
   */
  
  // Example of managing address
  struct in_addr in;

  if (argc != 2) {
    printf("Use: %s <decimal-punto>\n", argv[0]);
    exit(0);
  }

  if (inet_aton(argv[1], &in) == 0) {
    printf("Error in address\n");
    exit(0);
  }

  printf("Address is %s\n", inet_ntoa(in));


  /*
  * struct hostent *gethostbyname(char *str);
  * We pass the function the name in format <domain>.com , it gets the information of the host
  *
  * struct hostent *gethostbyaddr(const void *addr, int len, int type);
  * We pass the function an ip address, it returns the host information
  * addr is a pointer to the struct in_addr
  * len is the size of the the structure
  * type is AF_NET because this is between different devices, not like AF_UNIX
  */

  // Example of converting a domain dot address to a decimal address
  struct hostent *hp;
  /*
  struct hostent {
    char    *h_name;      // Official name of the host.
    char    **h_aliases;  // Null-terminated array of alternate names.
    int     h_addrtype;   // Host address type.
    int     h_length;     // Length of the address.
    char    **h_addr_list; // Null-terminated array of addresses.
  };
  */

  struct in_addr in2;
  
  hp = gethostbyname("www.uc3m.es");
  if (hp == NULL) {
    printf("Error in gethostbyname! \n");
    exit(1);
  }
  
  memcpy(&in2.s_addr, *(hp->h_addr_list), sizeof(in2.s_addr));
  printf("%s es %s\n", hp->h_name, inet_ntoa(in2));


  // USECASE
  
  struct in_addr addr;
  struct in_addr in3;
  struct hostent *hp2;
  char **p;
  char **q;
  int err2;

  if (argc != 2) {
    printf("Use: %s Address-IP\n", argv[0]);
    return 1;
  }
  // Use function aton (ascii to network), give it the address in decimal and it puts
  // the address in network form meaning binary it the struct addr
  err2 = inet_aton(argv[1], &addr);

  if (err2 == 0) {
    printf("Direccion IP en formato a.b.c.d\n");
    return (2);
  }

  // get the host info using the ip, we pass a pointer to the struct in_addr
  // which contains the address in binary, then the length of it, and the domain AF_INET
  hp2=gethostbyaddr((char *) &addr, sizeof(addr), AF_INET);
  // If it worked, hp2 will be populated

  if (hp2 == NULL) { 
    printf("Error en ....\n"); 
    return (3);
  }

  // loop through each address in the address list of hp2
  for (p = hp2->h_addr_list; *p!=0; p++) {
    // Write the address of the current iteration aka the current address in the list
    // in the in3 struct
    memcpy(&in3.s_addr, *p, sizeof(in3.s_addr));
    // print the ip address in decimal (Converted using ntoa) and the name of the address
    // aka the host details
    printf("%s es \t%s \n", inet_ntoa(in3), hp2->h_name); 
    for (q=hp2->h_aliases; *q != 0; q++) {
      // print the aliases
      printf("%s\n", *q);
    }
  }

  return 1;

}











