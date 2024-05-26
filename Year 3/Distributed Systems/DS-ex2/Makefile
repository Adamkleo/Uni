CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -L. -lclaves
LIB_NAME = libclaves.so

all: servidor cliente clientes

# Compile the servidor executable with message.o and claves.o
servidor: servidor.c message.o claves.o
	$(CC) $(CFLAGS) -o servidor servidor.c claves.o message.o

# Compile the cliente executable and dynamically link against libclaves.so
cliente: cliente.c $(LIB_NAME)
	$(CC) $(CFLAGS) -o cliente cliente.c $(LDFLAGS)

# Compile the clientes executable and dynamically link against libclaves.so
clientes: clientes.c $(LIB_NAME)
	$(CC) $(CFLAGS) -o clientes clientes.c $(LDFLAGS)

# Create the dynamic library from claves.o and message.o
$(LIB_NAME): claves.o message.o
	$(CC) -shared -o $(LIB_NAME) claves.o message.o

# Compile message.o
message.o: message.c message.h
	$(CC) $(CFLAGS) -fPIC -c message.c

# Ensure claves.o is recompiled if claves.h or message.h changes
claves.o: claves.c claves.h message.h
	$(CC) $(CFLAGS) -fPIC -c claves.c

clean:
	rm -f *.o servidor cliente clientes $(LIB_NAME)
	rm -r *.dSYM 

.PHONY: all clean
