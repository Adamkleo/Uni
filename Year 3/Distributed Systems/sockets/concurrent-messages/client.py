import socket
import sys

def readString(sock):
    """
    Reads a string message from the socket, skipping any leading null bytes and
    continuing until it encounters a terminating null byte.
    """
    a = ''
    while True:
        # Receive one byte at a time
        msg = sock.recv(1)
        
        # If this is the first byte and it's null, skip it and continue the loop
        if msg == b'\0' and not a:
            continue
        
        # Break the loop if a terminating null byte is found
        if msg == b'\0':
            break
        
        # Decode the byte and add it to the message string
        a += msg.decode()
    return a

def sendString(sock, message):
    """
    Sends a string message through the socket, appending a null byte at the end.
    """
    message += "\n"
    sock.sendall(message.encode())

def main(host, port):
    """
    Main function to connect to the server, send and receive messages.
    """
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_address = (host, port)
    print(f'Connecting to {host} port {port}')
    sock.connect(server_address)

    try:
        while True:
            # Sending a message to the server
            message = input("Enter message to send (or 'EXIT' to quit): ")
            sendString(sock, message)
            
            if message == "EXIT":
                print("Exiting...")
                break
            
            # Receiving a response from the server
            response = readString(sock)
            print(f"Received response: {response}")
            
    finally:
        print('Closing socket')
        sock.close()

if __name__ == "__main__":
    if len(sys.argv) < 3:
        print('Usage: python client.py <host> <port>')
        sys.exit()

    main(sys.argv[1], int(sys.argv[2]))

