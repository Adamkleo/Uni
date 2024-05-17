from cryptography.hazmat.primitives import serialization
from cryptography.hazmat.primitives.asymmetric import rsa
from cryptography import x509
from cryptography.x509.oid import NameOID
from cryptography.hazmat.primitives import hashes
import datetime

# Definición de la clase AC2
class AC2:
    def __init__(self) -> None:
        # Configuración de los atributos de la entidad de firmas digitales
        self.subject=x509.Name([x509.NameAttribute(NameOID.COUNTRY_NAME,"ES"),  # País
                                x509.NameAttribute(NameOID.STATE_OR_PROVINCE_NAME,"Madrid"),  # Comunidad Autónoma o Provincia
                                x509.NameAttribute(NameOID.LOCALITY_NAME,"Leganés"),  # Localidad
                                x509.NameAttribute(NameOID.ORGANIZATION_NAME,"UC3M"),  # Nombre de la Organización
                                x509.NameAttribute(NameOID.COMMON_NAME,"adam_rodrigo_AC2")])  # Nombre Común

        # Generación de una clave privada RSA
        key=rsa.generate_private_key(public_exponent=65537, key_size=2048)

        # Guardar la clave privada en un archivo
        with open("certificates/private_key_AC2.pem","wb") as f:
            f.write(key.private_bytes(
                encoding= serialization.Encoding.PEM,
                format=serialization.PrivateFormat.TraditionalOpenSSL,
                encryption_algorithm=serialization.BestAvailableEncryption(b"hola234")
            ))

        # Creación de una solicitud de firma de certificado (CSR)
        csr=x509.CertificateSigningRequestBuilder().subject_name(self.subject).sign(key,hashes.SHA256())

        # Guardar el CSR en un archivo
        with open("certificates/csrAC2.pem","wb")as f:
            f.write(csr.public_bytes(serialization.Encoding.PEM))
    
    # Método para crear el certificado de la entidad de firmas digitales
    def create_signature_entity_certificate(self):
        # Cargar la clave privada desde el archivo
        with open("certificates/private_key_AC2.pem","rb") as file:
            key=serialization.load_pem_private_key(file.read(),b"hola234")

        # Cargar el CSR desde el archivo
        with open("certificates/csr_signature_entity.pem","rb") as f:
            csr_sig=x509.load_pem_x509_csr(f.read())
            
        # Construir el certificado de la entidad de firmas digitales
        certificate_entity= x509.CertificateBuilder()
        certificate_entity=certificate_entity.subject_name(csr_sig.subject)
        certificate_entity=certificate_entity.issuer_name(self.subject)
        certificate_entity=certificate_entity.public_key(csr_sig.public_key())
        certificate_entity=certificate_entity.serial_number(x509.random_serial_number())
        certificate_entity=certificate_entity.not_valid_before(datetime.datetime.now(datetime.timezone.utc))
        certificate_entity = certificate_entity.not_valid_after(datetime.datetime.now(datetime.timezone.utc) + datetime.timedelta(days=50))
        certificate_entity=certificate_entity.sign(key,hashes.SHA256())

        # Guardar el certificado en un archivo
        with open("certificates/certificate_signature_entity.pem","wb") as f:
            f.write(certificate_entity.public_bytes(serialization.Encoding.PEM))
