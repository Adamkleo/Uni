all: operations storage clnt xdr svc servidor rpc_server  server cliente

operations:
	gcc -g -Wall   -D_REENTRANT -c -o operations.o operations.c

storage:
	gcc -g -Wall -I/usr/include/tirpc  -D_REENTRANT -c -o storage.o storage.c

rpc_server:
	gcc -g -Wall -I/usr/include/tirpc  -D_REENTRANT -c -o rpc_message_server.o rpc_message_server.c

clnt: rpc_message_clnt.c
	gcc -g -Wall -I/usr/include/tirpc -D_REENTRANT -c -o rpc_message_clnt.o rpc_message_clnt.c

servidor:
	gcc -g -Wall -I/usr/include/tirpc -D_REENTRANT -c -o servidor.o servidor.c -lnsl -lpthread -ldl -ltirpc

xdr: rpc_message_xdr.c
	gcc -g  -I/usr/include/tirpc -D_REENTRANT  -o rpc_message_xdr.o     -c rpc_message_xdr.c

svc: rpc_message_svc.c
	gcc -g  -I/usr/include/tirpc -D_REENTRANT  -o rpc_message_svc.o     -c rpc_message_svc.c



server: rpc_message_server.o  
	gcc -g -Wall -I./   -o servidor_rpc  rpc_message_svc.o  rpc_message_server.o rpc_message_xdr.o -lnsl -lpthread -ldl -ltirpc


cliente:servidor.o rpc_message_clnt.o rpc_message_xdr.o operations.o storage.o
	gcc -I/usr/include/tirpc -I./   -g -Wall  operations.o storage.o rpc_message_xdr.o rpc_message_clnt.o servidor.o -o  servidor  -lnsl  -lpthread -ldl -ltirpc

run:program_client
	env LD_LIBRARY_PATH=$LD_LIBRARY_PATH:. ./program_client


clean:
	rm -f servidor_rpc servidor *.o