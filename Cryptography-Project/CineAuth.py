from cryptography.hazmat.primitives import hashes
from cryptography.hazmat.backends import default_backend
from database import CinemaDatabase  # Import the CinemaDatabase class

class CinemaAuth:
    def __init__(self) -> None:
        self.db = CinemaDatabase()  # Initialize the CinemaDatabase
        self.username = None
        self.hashed_password = None

    def hash_password(self, password) -> None:
        digest = hashes.Hash(hashes.SHA256(), backend=default_backend())
        digest.update(password.encode())
        self.hashed_password = digest.finalize()

    def save_user(self):
        # Insert user into the database
        self.db.insert_user(self.username, self.hashed_password.hex())

    def register_user(self) -> int:
        self.username = input("Introduzca usuario: ").strip()
        if not self.username:
            return -1

        # Check if user already exists in the database
        if self.db.fetch_user(self.username):
            print("Nombre de usuario ya utilizado.")
            return -8
        
        password = input("Introduzca contraseña: ").strip()
        if not password:
            return -2

        self.hash_password(password)
        self.save_user()
        return 1

    def login(self) -> int:
        input_username = input("Introduzca usuario: ").strip()
        input_password = input("Introduzca contraseña: ").strip()

        if not input_username or not input_password:
            return -4

        user = self.db.fetch_user(input_username)

        if user:
            stored_hashed_password = bytes.fromhex(user[1])

            digest = hashes.Hash(hashes.SHA256(), backend=default_backend())
            digest.update(input_password.encode())
            input_hashed_password = digest.finalize()

            if stored_hashed_password == input_hashed_password:
                self.username = input_username
                return 1
            else:
                return -5
        else:
            return -7

# Rest of the error codes and comments remain the same

"""
1: Éxito
-1: Nombre de usuario vacío durante el registro
-2: Contraseña vacía durante el registro
-3: Ningún usuario registrado
-4: Nombre de usuario o contraseña vacía durante el inicio de sesión
-5: Contraseña incorrecta durante el inicio de sesión
-6: Firma no válida (error de desencriptación)
-7: Usuario no encontrado durante el inicio de sesión
-8: Nombre de usuario ya está en uso
"""