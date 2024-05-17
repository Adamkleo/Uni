import qrcode

# List of products
# List of products
products = [
    {"id": 1, "name": "Manzanas"},
    {"id": 2, "name": "Naranjas"},
    {"id": 3, "name": "Platanos"},
    {"id": 4, "name": "Huevos"},
    {"id": 5, "name": "Leche"},
    {"id": 6, "name": "Pan"},
    {"id": 7, "name": "Pechuga"},
    {"id": 8, "name": "Carne"},
    {"id": 9, "name": "Salmon"},
    {"id": 10, "name": "Arroz"},
    {"id": 11, "name": "Pasta"},
    {"id": 12, "name": "Tomates"},
    {"id": 13, "name": "Cebollas"},
    {"id": 14, "name": "Lechuga"},
    {"id": 15, "name": "Queso"},
    {"id": 16, "name": "Mantequilla"},
    {"id": 17, "name": "Yogur"},
    {"id": 18, "name": "Cafe"},
    {"id": 19, "name": "Te"},
    {"id": 20, "name": "Chocolate"}



]

# Generate QR code for each product
for product in products:
    img = qrcode.make(product['name'])
    img.save(f"{product['name'].lower()}.png")
