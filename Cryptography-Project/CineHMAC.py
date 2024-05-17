from cryptography.hazmat.primitives import hashes, hmac
from os import urandom
from cryptography.exceptions import InvalidSignature
from typing import Union
import logging

logging.basicConfig(level=logging.INFO, filename='test.log', filemode='w', format='%(asctime)s - %(levelname)s - %(message)s')

"""
CinemaHMAC es un patrón Singleton que agrega una etiqueta HMAC a los mensajes y también verifica la etiqueta de otros mensajes.
"""
class CinemaHMAC:
    _instance = None

    def __new__(cls) -> 'CinemaHMAC':
        if cls._instance is None:
            cls._instance = super(CinemaHMAC, cls).__new__(cls)
            cls._instance.key = urandom(32)
        return cls._instance

    # Agrega la clave HMAC a un mensaje
    def create_hmac(self, message: bytes) -> bytes:
        if not isinstance(message, bytes):
            raise TypeError("El mensaje deben ser bytes.")

        h = hmac.HMAC(self.key, hashes.SHA256())
        try:
            h.update(message)
        except Exception as e:
            raise RuntimeError(f"No se pudo crear HMAC: {e}")

        logging.info("Etiqueta HMAC se ha añadido al mensaje encriptado.")
        return h.finalize()

    # Verifica que la clave HMAC no haya cambiado, lo que significa que el mensaje no fue alterado.
    def verify_hmac(self, message: bytes, tag: bytes) -> Union[bool, None]:
        if not isinstance(message, bytes) or not isinstance(tag, bytes):
            raise TypeError("Mensaje y etiqueta deben ser bytes.")

        try:
            h = hmac.HMAC(self.key, hashes.SHA256())
            h.update(message)
            h.verify(tag)
            logging.info("HMAC verificada. No se ha modificado el pedido.")
            return True
        except InvalidSignature:
            return False
        except Exception as e:
            raise RuntimeError(f"Error en la verificación de HMAC: {e}")
            



