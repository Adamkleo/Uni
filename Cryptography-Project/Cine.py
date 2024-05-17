import re
from CineCrypto import CinemaCrypto
from CineHMAC import CinemaHMAC
from database import CinemaDatabase  # Import the CinemaDatabase class
from constants import TICKET_PRICE
from manage_signatures import signature_entity
"""
Cine: La lógica detrás de un cine, eligiendo una película, ordenando boletos y enviando la orden al procesador de pagos.
"""
class Cinema:

    def __init__(self, movies: tuple) -> None:
        self.movies = movies
        self.db = CinemaDatabase()
        
    # Imprime una lista de películas disponibles para comprar boletos.
    def _show_movies(self) -> None:
        for index, movie in enumerate(self.movies, start=1):
            print(f"({index}) - {movie}")

    # Pide al usuario que seleccione una película por su índice.
    def _select_movie(self) -> str:
        while True:
            user_choice = input("Elija una película por su número: ")

            if not user_choice.isdigit():
                print("Input no válido.Por favor introduzca un número.")
                continue

            user_choice = int(user_choice)

            if 1 <= user_choice <= len(self.movies):
                return self.movies[user_choice - 1]
            else:
                print("Elección no válida. Por favor introduzca un número de película válido.")

        # Función general que valida las entradas del usuario para los detalles de pago.
    def _is_valid(self, pattern, input_str):
        return bool(re.fullmatch(pattern, input_str))

    # Obtiene la información de la tarjeta de crédito de un usuario mediante una entrada.
    def _get_credit_info(self) -> dict:
        credit_info = {}
        
        card_number = self._get_valid_input("Introduzca su número de tarjeta de crédito de 16 dígitos: ", r'\d{16}', "Número de tarjeta de crédito no válido.")
        credit_info['card_number'] = card_number

        name = self._get_valid_input("Introduzca el nombre que aparece en la tarjeta: ", r'[A-Za-z\s]+', "Nombre no válido.")
        credit_info['name'] = name

        cvv = self._get_valid_input("Introduzca el CVV de 3 dígitos: ", r'\d{3}', "CVV no válido.")
        credit_info['cvv'] = cvv

        return credit_info

    # Compara la entrada de un usuario con un patrón de expresión regular para validarla.
    def _get_valid_input(self, prompt, pattern, error_msg):
        while True:
            user_input = input(prompt)
            if self._is_valid(pattern, user_input):
                return user_input
            else:
                print(error_msg)
                
    # Obtiene el número de boletos que el usuario desea comprar.
    def _get_ticket_count(self):
        while True:
            count = input("Cuántas entradas quieres comprar? ")
            if count.isdigit() and int(count) > 0:
                return int(count)
            else:
                print("Por favor introduzca un número válido de entradas.")

    """Proceso completo:
        - (1) Listar películas
        - (2) Seleccionar una película
        - (3) Elegir la cantidad de boletos
        - (4) Obtener información de la tarjeta de crédito
        - (5) Calcular el precio total
        - (6) Devolver un objeto con los detalles de la compra
    """
    def _purchase_ticket(self) -> tuple:
        self._show_movies()
        movie_choice = self._select_movie()
        ticket_count = self._get_ticket_count()
        credit_info = self._get_credit_info()
        total_price = ticket_count * TICKET_PRICE  # 6 euros por ticket

        return {"movie": movie_choice, "price": total_price, "payment_details": credit_info}
    

    def get_encrypted_order(self, username):
            purchase_details = self._purchase_ticket()
            purchase_details_message = f"{username}'s purchase: {purchase_details['movie']} for {purchase_details['price']} euros."

            # Encrypt the message and create HMAC
            encrypted_purchase_details = CinemaCrypto().encrypt_message(purchase_details_message)
            tag_encrypted_order = CinemaHMAC().create_hmac(encrypted_purchase_details)

            # Update order history in the database
            ticket_count = purchase_details['price'] / TICKET_PRICE
            self.update_order_history(username, purchase_details['movie'], ticket_count, purchase_details['price'])

            return {"message": purchase_details_message, "encrypted_message": encrypted_purchase_details, "tag_message": tag_encrypted_order}

    # Agrega un pedido encriptado al historial de pedidos de un usuario
    def update_order_history(self, username, movie_choice, ticket_count, total_price):
        cinema_crypto = CinemaCrypto()  # Initialize the CinemaCrypto instance

        # Encrypting the order details
        encrypted_movie = cinema_crypto.encrypt_message(movie_choice)
        encrypted_ticket_count = cinema_crypto.encrypt_message(str(ticket_count))  # Convert to string for encryption
        encrypted_total_price = cinema_crypto.encrypt_message(str(total_price))  # Convert to string for encryption

        # Inserting the encrypted order into the database
        self.db.insert_order(username, encrypted_movie, encrypted_ticket_count, encrypted_total_price)

    #Agregar una reseña a la base de datos
    def add_reviews(self,review_text,review_rating,username):
        #Firmar la reseña
        signature=signature_entity().sign_message(review_text)
        last_record=self.db.fetch_last_order()
        movie=last_record[2]
        movie=CinemaCrypto().decrypt_message(movie)
        self.db.insert_review(movie,review_text,signature,username,review_rating)

    #Comprobar las reseñas de la base de datos
    def check_reviews(self):
        record=self.db.fetch_last_review()
        review_text=record[2]
        signature=record[3]
        #Verificar la firma digital
        return signature_entity().verify_signature(review_text,signature)



