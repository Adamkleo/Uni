from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography import x509
from cryptography.x509.oid import NameOID
from cryptography.hazmat.primitives import hashes
import datetime

class AC1:
    
    def __init__(self) -> None:
        # Inicializar los atributos del sujeto para el certificado self-signed
        self.subject = x509.Name([
            x509.NameAttribute(NameOID.COUNTRY_NAME, "ES"),
            x509.NameAttribute(NameOID.STATE_OR_PROVINCE_NAME, "Madrid"),
            x509.NameAttribute(NameOID.LOCALITY_NAME, "Leganés"),
            x509.NameAttribute(NameOID.ORGANIZATION_NAME, "UC3M"),
            x509.NameAttribute(NameOID.COMMON_NAME, "adam_rodrigo_AC1")
        ])
        
        # Generar y guardar la clave privada
        key = rsa.generate_private_key(public_exponent=65537, key_size=2048)
        with open("certificates/private_key_AC1.pem", "wb") as f:
            f.write(key.private_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PrivateFormat.TraditionalOpenSSL,
                encryption_algorithm=serialization.BestAvailableEncryption(b"hola234")
            ))
        
        # Construir y guardar el certificado
        builder = x509.CertificateBuilder()
        builder = builder.subject_name(self.subject)
        builder = builder.issuer_name(self.subject)
        builder = builder.public_key(key.public_key())
        builder = builder.serial_number(x509.random_serial_number())
        builder = builder.not_valid_before(datetime.datetime.now(datetime.timezone.utc))
        builder = builder.not_valid_after(datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(days=200))
        builder = builder.sign(key, hashes.SHA256())

        with open("certificates/certificate_AC1.pem", "wb") as file:
            file.write(builder.public_bytes(serialization.Encoding.PEM))
        
    #Crear certificado de AC2
    def create_AC2_certificate(self):
        # Cargar la clave privada
        with open("certificates/private_key_AC1.pem", "rb") as file:
            key = serialization.load_pem_private_key(file.read(), b"hola234")
        
        # Cargar la solicitud de firma de certificado (CSR) para AC2
        with open("certificates/csrAC2.pem", "rb") as f:
            csr_AC2 = x509.load_pem_x509_csr(f.read())
            
        # Construir y guardar el certificado para AC2
        AC2_certificate = x509.CertificateBuilder()
        AC2_certificate = AC2_certificate.subject_name(csr_AC2.subject)
        AC2_certificate = AC2_certificate.issuer_name(self.subject)
        AC2_certificate = AC2_certificate.public_key(csr_AC2.public_key())
        AC2_certificate = AC2_certificate.serial_number(x509.random_serial_number())
        AC2_certificate = AC2_certificate.not_valid_before(datetime.datetime.now(datetime.timezone.utc))
        AC2_certificate = AC2_certificate.not_valid_after(datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(days=100))
        AC2_certificate = AC2_certificate.sign(key, hashes.SHA256())

        with open("certificates/certificate_AC2.pem", "wb") as f:
            f.write(AC2_certificate.public_bytes(serialization.Encoding.PEM))
