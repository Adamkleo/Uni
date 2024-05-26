## Compilation
To compile, simply run `make`. This will generate two executables, one for the client and one for the server, as well as one for the concurrent test, clients. To run, follow the steps below:

- For the server:
    ```
    ./servidor <PORT>
    ```
- For `cliente.c`:
    ```
    env IP_TUPLAS=localhost PORT_TUPLAS=<PORT> ./cliente
    ```
- For `clientes.c`:
    ```
    env IP_TUPLAS=localhost PORT_TUPLAS=<PORT> ./clientes
    ```

Replace `<PORT>` with your chosen port, for example, 2000.

