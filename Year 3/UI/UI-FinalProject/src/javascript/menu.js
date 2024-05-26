document.addEventListener("DOMContentLoaded", function() {
    const menuItems = [
        { name: "Sushi Maki Clásico (8 piezas)", description: "Arroz, alga nori, salmón, aguacate, pepino", price: "8.00 €" },
        { name: "Ramen de Miso con Tofu", description: "Caldo miso, fideos ramen, tofu, cebolla verde, algas", price: "10.00 €" },
        { name: "Donburi de Pollo Teriyaki", description: "Arroz, pollo teriyaki, cebollín, semillas de sésamo", price: "9.50 €" },
        { name: "Tempura de Verduras Mixtas", description: "Verduras variadas, harina tempura, salsa soja", price: "7.50 €" },
        { name: "Ensalada de Wakame", description: "Alga wakame, pepino, salsa de sésamo, vinagre de arroz", price: "6.00 €" },
        { name: "Gyozas de Verduras (6 piezas)", description: "Masa de gyoza, verduras variadas, salsa soja", price: "7.00 €" },
        { name: "Bento Box Vegetariano", description: "Arroz, tempura de verduras, ensalada de wakame, tofu", price: "12.00 €" },
        { name: "Takoyaki (6 piezas)", description: "Masa de takoyaki, pulpo, cebolla verde, salsa takoyaki", price: "8.00 €" },
        { name: "Edamame con Sal Marina", description: "Edamame, sal marina", price: "5.00 €" },
        { name: "Helado de Té Verde Matcha", description: "Té verde matcha, leche, azúcar", price: "4.50 €" }
    ];

    const menuContainer = document.createElement('div');
    menuContainer.className = 'menu-container';

    menuItems.forEach(item => {
        const menuItem = document.createElement('div');
        menuItem.className = 'menu-item';

        const name = document.createElement('div');
        name.className = 'menu-item-name';
        name.innerHTML = `<b>${item.name}</b>`;

        const description = document.createElement('div');
        description.className = 'menu-item-description';
        description.textContent = item.description;

        const price = document.createElement('div');
        price.className = 'menu-item-price';
        price.textContent = item.price;
        price.style.color = 'black';

        menuItem.appendChild(name);
        menuItem.appendChild(description);
        menuItem.appendChild(price);

        menuContainer.appendChild(menuItem);
    });

    const container = document.querySelector('.custom-container');
    container.insertAdjacentElement('afterend', menuContainer);
});
