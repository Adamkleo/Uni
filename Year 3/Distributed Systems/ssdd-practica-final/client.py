from enum import Enum
import argparse, threading, socket
from utils import readLine, readString, parseUserList
from typing import Tuple

import zeep



class client:

    # ******************** TYPES *********************
    # *
    # * @brief Return codes for the protocol methods
    class RC(Enum):
        OK = 0
        ERROR = 1
        USER_ERROR = 2

    # ****************** ATTRIBUTES ******************
    _server = None
    _port = -1
    _keep_running = True
    _listen_sock = None
    _username = None
    connected_users={}

    # ******************** METHODS *******************

    @staticmethod
    def _getServerTime():
        wsdl_url = "http://localhost:8000/?wsdl"
        soap_client = zeep.Client(wsdl=wsdl_url)
        return soap_client.service.get_time()


    @staticmethod
    def _initSocket() -> socket.socket:
        # Creación de socket
        sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_address = (client._server, client._port)
        # Conectar el socket al server
        sock.connect(server_address)
        return sock

    @staticmethod
    def _connectToUser(username: str) -> socket.socket:
        # Creación de socket
        sock= socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        # Address y port del usuario
        user_address= (client.connected_users[username][0], int(client.connected_users[username][1]))
        # Conectar el socket al usuario
        sock.connect(user_address)
        return sock

    @staticmethod
    def _sendTuple(sock: socket, args: Tuple) -> None:
        if not args:
            return  # Return temprano si args está vacío para prevenir errores

        # Codificamos el primer argumento y añadimos la string de datetime
        first_arg = args[0].encode('utf-8') + b'\0'
        datetime_str = client._getServerTime()
        datetime_message = f" {datetime_str} ".encode('utf-8') + b'\0'

        # Codificar el resto de argumentos
        rest_args = b''.join(arg.encode('utf-8') + b'\0' for arg in args[1:])

        # Concatenar el mensaje completo
        full_message = first_arg + datetime_message + rest_args

        # Mandar el mensaje completo
        sock.sendall(full_message)




    @staticmethod
    def _updateUsers(user: str) -> None:
        # Creación de socket
        sock = client._initSocket()
        client._sendTuple(sock, ("UPDATE_USERS", user, str(client._listen_port)))
        sock.close()

    @staticmethod
    def register(user: str) -> int:

        # Mensaje de operación
        operation = "REGISTER"
        response = None

        # Creación de tupla de socket y conexión
        sock = client._initSocket()

        try:

            # Mandar mensaje y usuario al server
            client._sendTuple(sock, (operation, user))
     
            # Leer respuesta del server y cerrar el socket
            response = readLine(sock)
            response = int(response)
            
            if response == -1:
                print("c> REGISTER FAIL")
                return client.RC.ERROR

            sock.close()

        except Exception as e:
            print(f"Failed to register. Error: {e}")
            return client.RC.ERROR

        if response == 0:
            print("c> REGISTER OK")
            return client.RC.OK
        if response == 1:
            print("c> USERNAME IN USE")
            return client.RC.USER_ERROR
        if response == 2:
            print("c> REGISTER FAIL")
            return client.RC.ERROR

        return client.RC.ERROR

    @staticmethod
    def unregister(user: str) -> int:

        # Mensaje de operación
        operation = "UNREGISTER"
        response = None

        # Creación de la socket tuple
        sock = client._initSocket()


        try:

            # Mandar mensaje y username al server
            client._sendTuple(sock, (operation, user))
     
            # Leer respuesta del server y cerrar socket
            response = readLine(sock)
            response = int(response)

            sock.close()
        
        except Exception as e:
            print("c> UNREGISTER FAIL")
            return client.RC.ERROR
        
        if response == 0:
            print("c> UNREGISTER OK")
            client._username = None
            client._keep_running = False
            client._listen_sock = None
            return client.RC.OK
        if response == 1:
            print("c> USER DOES NOT EXIST")
            return client.RC.USER_ERROR
        if response == 2:
            return client.RC.ERROR
        

        return client.RC.ERROR

    @staticmethod
    def connect(user: str) -> int:

        if not bool(user and user.strip()):
            print("c> CONNECT FAIL")
            return client.RC.ERROR

        if client._username and client._username != user:
            print("c> CONNECT FAIL")
            return client.RC.ERROR            
        if client._username == user:
            print("c> USER ALREADY CONNECTED")
            return client.RC.USER_ERROR
        # Conexión principal al server
        
        operation = "CONNECT"


        try:
            client._keep_running = True
            
            # Setup y verificar que el socket está escuchando antes de iniciar el hilo
            client._listen_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            client._listen_sock.bind(('', 0))  # Cualquier puerto
            client._listen_sock.listen()
            client._listen_port = client._listen_sock.getsockname()[1]

            sock = client._initSocket()

            # Mandar mensaje y nombre de usuario al server
            client._sendTuple(sock, (operation, user))
     



            
            # Ahora que el socket está escuchando, iniciar el thread
            threading.Thread(target=client.handle_incoming, args=(user,), daemon=True).start()


            
            # Esperar a la respuesta del server
            response = readLine(sock)
            response = int(response)

            if response == -1:
                print("c> CONNECT FAIL")
                return client.RC.ERROR

            if response == 0:
                print("c> CONNECT OK")
                client._username = user
                return client.RC.OK
            elif response == 1:
                print("c> CONNECT FAIL, USER DOES NOT EXIST")
                return client.RC.USER_ERROR
            elif response == 2:
                print("c> USER ALREADY CONNECTED")
                return client.RC.ERROR
            elif response == 3:
                print("c> CONNECT FAIL")
                return client.RC.ERROR
        except Exception as e:
            print(f"Failed to connect. Error: {e}")
            return client.RC.ERROR
        finally:
            sock.close()



    @staticmethod
    def handle_incoming(user: str) -> None:
        while client._keep_running:
            client._updateUsers(user)
            client_sock, addr = client._listen_sock.accept()
            try:
                data = client_sock.recv(1024)
                while data:
                    decoded_data = data.decode('utf-8').split('\0')
                    command = decoded_data[0]
                    
                    if command == "GET_FILE" and len(decoded_data) >= 3:
                        remote_FileName = decoded_data[1].strip()
                        try:
                            with open(remote_FileName, 'rb') as f:
                                client_sock.sendall(b'0')  # Indicar que el archivo se va a enviar
                                bytes_read = f.read(1024)
                                while bytes_read:
                                    client_sock.sendall(bytes_read)
                                    bytes_read = f.read(1024)
                                client_sock.sendall(b'EOF')  # Mandar señal EOF
                        except FileNotFoundError:
                            client_sock.sendall(b'1')  # Archivo no encontrado
                            print("File not found:", remote_FileName)  # Debug print
                        except Exception as e:
                            client_sock.sendall(b'2')  # Otros errores
                            print("Error:", e)  # Debug print
                    data = client_sock.recv(1024)
            finally:
                client_sock.close()






 

    @staticmethod
    def disconnect(user):

        if not client._username:
            print("c> DISCONNECT FAIL, USER NOT CONNECTED")
            return client.RC.USER_ERROR
        
        if client._username != user:
            print("c> DISCONNECT FAIL")
            return client.RC.ERROR
        # Mensaje de operación
        operation = "DISCONNECT"

        # Crear un socket
        sock = client._initSocket()


        try:

            # Mandar mensaje y nombre de usuario al servidor
            client._sendTuple(sock, (operation, user))
     
            # Esperar a la respuesta del server
            response = readLine(sock)
            response = int(response)
            sock.close()

   

            if response == 0:
                print("c> DISCONNECT OK")
                client._username = None
                client._keep_running = False
                client._listen_sock = None   # Resetear a None

                return client.RC.OK
            elif response == 1:
                print("c> DISCONNECT FAIL / USER DOES NOT EXIST")
                return client.RC.USER_ERROR
            elif response == 2:
                print("c> DISCONNECT FAIL / USER NOT CONNECTED")
                return client.RC.USER_ERROR
            elif response == 3:
                print("c> DISCONNECT FAIL")
                return client.RC.ERROR
        except Exception as e:
            print(f"Failed to disconnect. Error: {e}")
            return client.RC.ERROR


    @staticmethod
    def publish(fileName, description):
        if not client._username:
            print("c> PUBLISH FAIL, USER NOT CONNECTED")
            return client.RC.USER_ERROR

        operation = "PUBLISH"

        sock = client._initSocket()

        try:
            # Mandar comando PUBLISH
            client._sendTuple(sock, (operation, client._username, fileName, description))

            # Esperar a la respuesta del server
            response = readLine(sock)
            response = int(response)
            sock.close()

            if response == 0:
                print("c> PUBLISH OK")
                return client.RC.OK
            elif response == 1:
                print("c> PUBLISH FAIL, USER DOES NOT EXIST")
                return client.RC.USER_ERROR
            elif response == 2:
                print("c> PUBLISH FAIL, USER NOT CONNECTED")
                return client.RC.USER_ERROR
            elif response == 3:
                print("c> PUBLISH FAIL, CONTENT ALREADY PUBLISHED")
                return client.RC.USER_ERROR
            elif response == 4:
                print("c> PUBLISH FAIL")
                return client.RC.ERROR
        except Exception as e:
            print(f"Failed to publish. Error: {e}")
            return client.RC.ERROR


    @staticmethod
    def delete(fileName):

        if not client._username:
            print("c> DELETE FAIL, USER NOT CONNECTED")
            return client.RC.USER_ERROR
        
        # Mensaje de operación
        operation = "DELETE"

        sock = client._initSocket()

        try:

            client._sendTuple(sock, (operation, client._username, fileName))

            # Esperar a la respuesta del server
            response = readLine(sock)
            response = int(response)
            sock.close()

            if response == 0:
                print("c> DELETE OK")
                return client.RC.OK
            elif response == 1:
                print("c> DELETE FAIL, USER DOES NOT EXIST")
                return client.RC.USER_ERROR
            elif response == 2:
                print("c> DELETE FAIL, USER NOT CONNECTED")
                return client.RC.USER_ERROR
            elif response == 3:
                print("c> DELETE FAIL, CONTENT NOT PUBLISHED")
                return client.RC.USER_ERROR
            elif response == 4:
                print("c> DELETE FAIL")
                return client.RC.ERROR
        except Exception as e:
            print(f"Failed to publish. Error: {e}")
            return client.RC.ERROR


    @staticmethod
    def listusers():
        if not client._username:
            print("c> LIST_USERS FAIL, USER NOT CONNECTED")
            return client.RC.USER_ERROR

        operation = "LIST_USERS"
        sock = client._initSocket()

        try:

            client._sendTuple(sock, (operation, client._username))

            # Esperar a la respuesta del server(result code)
            result = readLine(sock)
            result = int(result)

            if result == 0:
                # Si es exitoso, leer la siguiente parte (user list)
                user_list = readString(sock)
                client.connected_users = parseUserList(user_list)
                print("c> LIST_USERS OK")
                print(user_list)
            elif result == 1:
                print("c> LIST_USERS FAIL, USER DOES NOT EXIST")
            elif result == 2:
                print("c> LIST_USERS FAIL, USER NOT CONNECTED")
            else:
                print("c> LIST_USERS FAIL")

        except Exception as e:
            print(f"Error: {e}")
        finally:
            sock.close()

        return client.RC.ERROR

    @staticmethod
    def listcontent(user):
        operation = "LIST_CONTENT"
        
        sock = client._initSocket()

        try:
            
            client._sendTuple(sock, (operation, client._username, user))

            # Esperar a la respuesta del servidor (result code)
            result = readLine(sock)
            result = int(result)

            if result == 0:
                # Si es exitoso, leer la siguiente parte (user list)
                content_list = readString(sock)
                print("c> LIST_CONTENT OK")
                print(content_list)
            elif result == 1:
                print("c> LIST_CONTENT FAIL, USER DOES NOT EXIST")
            elif result == 2:
                print("c> LIST_CONTENT FAIL, USER NOT CONNECTED")
            elif result == 3:
                print("c> LIST_CONTENT FAIL, REMOTE USER DOES NOT EXIST")
            else:
                print("c> LIST_CONTENT FAIL")

        except Exception as e:
            print(f"Error: {e}")
        finally:
            sock.close()

        return client.RC.ERROR
    
    
    @staticmethod
    def getfile(user, remote_FileName, local_FileName):
        operation = "GET_FILE"
        sock = client._connectToUser(user)
        try:


            sock.sendall(operation.encode('utf-8') + b'\0')
            sock.sendall(remote_FileName.encode('utf-8') + b'\0')
            
            response = sock.recv(1)
            if response == b'0':
                with open(local_FileName, 'wb') as f:
                    while True:
                        data = sock.recv(1024)
                        if b'EOF' in data:
                            f.write(data[:-3])  # Escribir datos sin EOF
                            break
                        f.write(data)
                print("c> GET_FILE OK")
                return client.RC.OK
            elif response == b'1':
                print("c> GET_FILE FAIL / FILE NOT EXIST")
                return client.RC.USER_ERROR
            elif response == b'2':
                print("c> GET_FILE FAIL")
                return client.RC.ERROR
        except Exception as e:
            print(f"Error: {e}")
            return client.RC.ERROR
        finally:
            sock.close()


    # *
    # **
    # * @brief Command interpreter for the client. It calls the protocol functions.
    @staticmethod
    def shell():

        while (True):
            try:
                command = input("c> ")
                line = command.split(" ")
                if (len(line) > 0):

                    line[0] = line[0].upper()

                    if (line[0] == "REGISTER"):
                        if (len(line) == 2):
                            client.register(line[1])
                        else:
                            print("Syntax error. Usage: REGISTER <userName>")

                    elif (line[0] == "UNREGISTER"):
                        if (len(line) == 2):
                            client.unregister(line[1])
                        else:
                            print("Syntax error. Usage: UNREGISTER <userName>")

                    elif (line[0] == "CONNECT"):
                        if (len(line) == 2):
                            client.connect(line[1])
                        else:
                            print("Syntax error. Usage: CONNECT <userName>")

                    elif (line[0] == "PUBLISH"):
                        if (len(line) >= 3):
                            #  Remove first two words
                            description = ' '.join(line[2:])
                            client.publish(line[1], description)
                        else:
                            print(
                                "Syntax error. Usage: PUBLISH <fileName> <description>")

                    elif (line[0] == "DELETE"):
                        if (len(line) == 2):
                            client.delete(line[1])
                        else:
                            print("Syntax error. Usage: DELETE <fileName>")

                    elif (line[0] == "LIST_USERS"):
                        if (len(line) == 1):
                            client.listusers()
                        else:
                            print("Syntax error. Use: LIST_USERS")

                    elif (line[0] == "LIST_CONTENT"):
                        if (len(line) == 2):
                            client.listcontent(line[1])
                        else:
                            print("Syntax error. Usage: LIST_CONTENT <userName>")

                    elif (line[0] == "DISCONNECT"):
                        if (len(line) == 2):
                            client.disconnect(line[1])
                        else:
                            print("Syntax error. Usage: DISCONNECT <userName>")

                    elif (line[0] == "GET_FILE"):
                        if (len(line) == 4):
                            client.getfile(line[1], line[2], line[3])
                        else:
                            print(
                                "Syntax error. Usage: GET_FILE <userName> <remote_fileName> <local_fileName>")

                    elif (line[0] == "QUIT"):
                        if (len(line) == 1):
                            client.disconnect(client._username)
                            break
                        else:
                            print("Syntax error. Use: QUIT")
                    else:
                        print("Error: command " + line[0] + " not valid.")
            except Exception as e:
                print("Exception: " + str(e))

    # *
    # * @brief Prints program usage
    @staticmethod
    def usage():
        print("Usage: python3 client.py -s <server> -p <port>")

    # *
    # * @brief Parses program execution arguments

    @staticmethod
    def parseArguments(argv):
        parser = argparse.ArgumentParser()
        parser.add_argument('-s', type=str, required=True, help='Server IP')
        parser.add_argument('-p', type=int, required=True, help='Server Port')
        args = parser.parse_args()

        if (args.s is None):
            parser.error("Usage: python3 client.py -s <server> -p <port>")
            return False

        if ((args.p < 1024) or (args.p > 65535)):
            parser.error(
                "Error: Port must be in the range 1024 <= port <= 65535")
            return False

        client._server = args.s
        client._port = args.p

        return True

    # ******************** MAIN *********************

    @staticmethod
    def main(argv):
        if (not client.parseArguments(argv)):
            client.usage()
            return

        #  Write code here
        client.shell()
        print("+++ FINISHED +++")


if __name__ == "__main__":
    client.main([])
