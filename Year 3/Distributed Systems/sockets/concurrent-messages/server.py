import socket
import threading



 
def handle_client(client_socket, client_address):
    print(f"Connection from {client_address}")
    try:
       while True:
            message = read_message(client_socket)
            if message == "EXIT":
                print(f"Client {client_address} disconnected.")
                break
            # Echo back the received message
            client_socket.sendall((message + '\0').encode())
    finally:
        client_socket.close()


def read_message(sock):
    message = ''
    while True:
        char = sock.recv(1).decode()  # Receive one character at a time
        if char == '\n':  # Check if it's the end of the message
            break
        message += char
    return message

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
sock.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
server_address = ('localhost', 2000)
sock.bind(server_address)
sock.listen(5)

print("Server is listening on port 2000")

while True:
    print("Waiting for a connection.")
    connection, client_address = sock.accept()

    thread = threading.Thread(target=handle_client, args=(connection, client_address))

    thread.start()
    
    

