from cryptography.fernet import Fernet
from Crypto.PublicKey import RSA
from Crypto.Signature import pkcs1_15
import logging
from Crypto.Hash import SHA256
logging.basicConfig(level=logging.INFO, filename='test.log', filemode='w', format='%(asctime)s - %(levelname)s - %(message)s')

"""
CinemaCrypto es un Singleton que cifra y descifra mensajes.
"""
class CinemaCrypto:
    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(CinemaCrypto, cls).__new__(cls)
            cls._instance.generate_encryption_key()
        return cls._instance

    # Genera la clave privada que se utilizará para el cifrado FERNET
    def generate_encryption_key(self):
        self.encryption_key = Fernet.generate_key()
        self.cipher = Fernet(self.encryption_key)
        logging.info(f"Encryption key generada. Algoritmo: Fernet, Longitud de clave: 256 bits")

    # Toma un mensaje y lo cifra utilizando Fernet
    def encrypt_message(self, message):
        encrypted_message = self.cipher.encrypt(message.encode())
        logging.info(f"Mensaje encriptado: {encrypted_message}")
        return encrypted_message

    # Toma un mensaje cifrado con Fernet y lo descifra
    def decrypt_message(self, encrypted_message):
        decrypted_message = self.cipher.decrypt(encrypted_message).decode()
        logging.info(f"Mensaje desencriptado: {decrypted_message}")
        return decrypted_message

    

    

    
