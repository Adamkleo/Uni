from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography import x509
from cryptography.x509.oid import NameOID
from cryptography.hazmat.primitives.asymmetric import padding
from cryptography.hazmat.primitives import hashes
from Crypto.PublicKey import RSA
from Crypto.Hash import SHA256
import logging

# Clase para la entidad de firma digital
class signature_entity:

    _instance = None

    def __new__(cls):
        if cls._instance is None:
            cls._instance = super(signature_entity, cls).__new__(cls)

            # Generación de la clave privada para firma digital
            key = rsa.generate_private_key(public_exponent=65537, key_size=2048)
            logging.info("Generada la clave de firma digital. Algoritmo: RSA, Tamaño de clave: 2048 bits")

            # Guardar la clave privada en un archivo
            with open("certificates/private_key_signature_entity.pem","wb") as f:
                f.write(key.private_bytes(
                    encoding=serialization.Encoding.PEM,
                    format=serialization.PrivateFormat.TraditionalOpenSSL,
                    encryption_algorithm=serialization.BestAvailableEncryption(b"hola234")
                ))

            # Creación de una solicitud de firma de certificado (CSR)
            csr = x509.CertificateSigningRequestBuilder().subject_name(x509.Name([
                x509.NameAttribute(NameOID.COUNTRY_NAME, "ES"),
                x509.NameAttribute(NameOID.STATE_OR_PROVINCE_NAME, "Madrid"),
                x509.NameAttribute(NameOID.LOCALITY_NAME, "Leganés"),
                x509.NameAttribute(NameOID.ORGANIZATION_NAME, "UC3M"),
                x509.NameAttribute(NameOID.COMMON_NAME, "adam_rodrigo_signature_entity")
            ])).sign(key, hashes.SHA256())

            # Guardar el CSR en un archivo
            with open("certificates/csr_signature_entity.pem", "wb") as f:
                f.write(csr.public_bytes(serialization.Encoding.PEM))
        return cls._instance

    # Método para firmar un mensaje
    def sign_message(self, message):
        with open("certificates/private_key_signature_entity.pem", "rb") as file:
            private_key = serialization.load_pem_private_key(file.read(), b"hola234")
        
        # Firmar el mensaje
        signature = private_key.sign(message.encode(), padding.PSS(mgf=padding.MGF1(hashes.SHA256()), salt_length=padding.PSS.MAX_LENGTH), hashes.SHA256())
        return signature

    # Método para verificar una firma
    def verify_signature(self, message, signature):
        with open("certificates/certificate_signature_entity.pem", "rb") as f:
            signed_certificate = x509.load_pem_x509_certificate(f.read())
        
        public_key = signed_certificate.public_key()
        try:
            # Verificar la firma
            public_key.verify(signature, message.encode(), padding.PSS(mgf=padding.MGF1(hashes.SHA256()), salt_length=padding.PSS.MAX_LENGTH), hashes.SHA256())
            return True
        except Exception:
            return False
