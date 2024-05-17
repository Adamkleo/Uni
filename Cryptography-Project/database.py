import sqlite3

# Clase para la base de datos del cine
class CinemaDatabase:
    def __init__(self, db_name="cinema.db"):
        self.db_name = db_name
        self.conn = None
        self.initialize_database()

    def connect(self):
        self.conn = sqlite3.connect(self.db_name)
        return self.conn.cursor()

    def close(self):
        if self.conn:
            self.conn.commit()
            self.conn.close()
            self.conn = None

    def initialize_database(self):
        cursor = self.connect()

        # Crear la tabla de usuarios si no existe
        cursor.execute('''CREATE TABLE IF NOT EXISTS users
                          (username TEXT PRIMARY KEY, password_hash TEXT)''')

        # Crear la tabla de pedidos si no existe
        cursor.execute('''CREATE TABLE IF NOT EXISTS orders
                          (order_id INTEGER PRIMARY KEY AUTOINCREMENT, 
                           username TEXT, 
                           movie TEXT, 
                           ticket_count INTEGER, 
                           total_price REAL,
                           FOREIGN KEY (username) REFERENCES users(username))''')
        
        # Crear la tabla de reseñas si no existe
        cursor.execute('''CREATE TABLE IF NOT EXISTS reviews
                       (review_id INTEGER PRIMARY KEY AUTOINCREMENT,
                       movie TEXT,
                       review_text TEXT,
                       signature BLOB,
                       username TEXT,
                       rating INTEGER,
                       FOREIGN KEY(username) REFERENCES users(username))''')
        self.close()

    # Insertar una reseña en la base de datos
    def insert_review(self, movie, review_text, signature, username, rating):
        cursor = self.connect()
        cursor.execute("INSERT INTO reviews (movie, review_text, signature, username, rating) VALUES (?, ?, ?, ?, ?)",
                       (movie, review_text, signature, username, rating))
        self.close()
    
    # Insertar un usuario en la base de datos
    def insert_user(self, username, password_hash):
        cursor = self.connect()
        cursor.execute("INSERT INTO users (username, password_hash) VALUES (?, ?)", 
                       (username, password_hash))
        self.close()

    # Obtener información de un usuario por su nombre de usuario
    def fetch_user(self, username):
        cursor = self.connect()
        cursor.execute("SELECT * FROM users WHERE username=?", (username,))
        user = cursor.fetchone()
        self.close()
        return user

    # Agregar métodos para insertar y obtener pedidos
    def insert_order(self, username, movie, ticket_count, total_price):
        cursor = self.connect()
        cursor.execute("INSERT INTO orders (username, movie, ticket_count, total_price) VALUES (?, ?, ?, ?)", 
                       (username, movie, ticket_count, total_price))
        self.close()

    def fetch_orders(self, username):
        cursor = self.connect()
        cursor.execute("SELECT * FROM orders WHERE username=?", (username,))
        orders = cursor.fetchall()
        self.close()
        return orders
    
    # Obtener el último pedido realizado
    def fetch_last_order(self):
        cursor = self.connect()
        cursor.execute("SELECT * FROM orders ORDER BY order_id DESC LIMIT 1")
        return cursor.fetchone()

    # Obtener la última reseña realizada
    def fetch_last_review(self):
        cursor = self.connect()
        cursor.execute("SELECT * FROM reviews ORDER BY review_id DESC LIMIT 1")
        return cursor.fetchone()
