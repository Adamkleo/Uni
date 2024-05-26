import logging
from CineAuth import CinemaAuth
from CineCrypto import CinemaCrypto
from Cine import Cinema
from CineHMAC import CinemaHMAC
from AC1 import AC1
from AC2 import AC2
from manage_signatures import signature_entity
# Inicializar configuración de logging
logging.basicConfig(level=logging.INFO, filename='crypto.log', filemode='w', format='%(asctime)s - %(levelname)s - %(message)s')

# Mostrar menú y obtener elección del usuario para login o register
def show_menu():
    choice = 0
    while choice not in ("1", "2"):
        choice = input("(1) Login \n(2) Register \nEnter: ")
    return choice

# Maneja autenticación de usuario
def authenticate(auth_system):
    logged_in = False
    while not logged_in:
        user_choice = show_menu()

        if user_choice == "1":  # Login
            result = auth_system.login()
            if result == 1:
                logged_in = True
            else:
                print(f"Login falló con número de error {result}.")

        elif user_choice == "2":  # Register
            result = auth_system.register_user()
            if result == 1:
                print("Registro con éxito. Por favor haga login.")
            else:
                print(f"Registro falló con código de error {result}.")
    return True

#Preguntar al usuario si quiere escribir una reseña
def ask_review(cinema,username):
    choice=input("Quieres dejar una reseña para la película? (1) Dejar una reseña  (2) Finalizar: ")
    if choice=="1":

        review_text=input("Escriba su reseña: ")
        rating= input("Valore la película con un número del 1 al 5, siendo 1 el más bajo y 5 el más alto: ")
        cinema.add_reviews(review_text,rating,username)
        logging.info("Se ha procesado la reseña")
        return 1

# Main function
def main():
    cinema_crypto = CinemaCrypto()  # Inicializar cryptography
    cinema_hmac = CinemaHMAC()  # Inicializar HMAC
    ac1=AC1()
    ac2=AC2()
    sig_entity=signature_entity()
    ac1.create_AC2_certificate()
    ac2.create_signature_entity_certificate()
    # Inicializar cine y auth_system
    cinema = Cinema(("Inception", "The Matrix", "Pulp Fiction", "The Dark Knight", "Shawshank Redemption"))
    auth_system = CinemaAuth()

    if authenticate(auth_system):  # Si la autenticación es exitosa
        # Obtener detalles de pedido encriptados
        order_details = cinema.get_encrypted_order(auth_system.username)
        original_order = order_details['message']

        logging.info("Pedido se ha mandado al cine.")
        
        encrypted_order = order_details['encrypted_message']
        tag = order_details["tag_message"]

        # Verificar la integridad del pedido usando HMAC
        order_tag_verified = cinema_hmac.verify_hmac(encrypted_order, tag)

        logging.info("Order decrypting.")
        decrypted_order = cinema_crypto.decrypt_message(encrypted_order)
        


        if order_tag_verified:
            if order_tag_verified and (decrypted_order == original_order):
                logging.info("Encriptación y decriptación exitosas.")
            else:
                logging.error("Encriptación y decriptación fallaron.")
        else:
            logging.error("Verificación HMAC fallida. Puede que se hayan alterado los datos del pedido.")
        
        #Comprobar si el usuario quiere escribir una reseña para la película
        review=ask_review(cinema,auth_system.username)

        #Verificar firma digital
        if review:
            if not cinema.check_reviews():
                logging.error("Verificación de firma digital fallida")
            else:
                logging.info("Verificación de firma digital exitosa")
            
        


if __name__ == "__main__":
    main()
