document.addEventListener("DOMContentLoaded", () => {
    let totalSum = 0; // Inicializa el precio total
    let totalDishes = 0; // Inicializa el número total de platos
    const dishesSelected = {}; // Inicializa un objeto para hacer un seguimiento de los platos seleccionados

    const menuItems = [ // Define un array de elementos de menú con nombres y precios
        { name: "Paella", price: 10 },
        { name: "Tortilla Española", price: 10 },
        { name: "Gazpacho", price: 15 },
        { name: "Pulpo a la Gallega", price: 15 },
        { name: "Sushi", price: 20 },
        { name: "Tempura", price: 20 },
        { name: "Ramen", price: 30 },
        { name: "Okonomiyaki", price: 30 }
    ];

    const productsSection = document.getElementById("products"); // Obtiene la sección de productos del HTML
    const totalPriceElement = document.getElementById("total-price"); // Obtiene el elemento para mostrar el precio total
    totalPriceElement.classList.add("card-subtitle"); // Agrega una clase CSS para dar estilo
    const totalDishesElement = document.getElementById("total-dishes"); // Obtiene el elemento para mostrar el número total de platos
    totalDishesElement.classList.add("card-subtitle"); //Añadir CSS para estilo

    function updateTotal() {
        // Actualiza el precio total y los platos elegidos
        totalPriceElement.textContent = `Total Price: ${totalSum}€`;
        totalDishesElement.textContent = `Total Dishes: ${totalDishes}`;

        // Crea un evento personalizado y lo despacha con los platos seleccionados actualizados
        const event = new CustomEvent('dishesUpdated', { detail: dishesSelected });
        document.dispatchEvent(event);
    }

    // Itera a través de los elementos del menú y crea elementos para cada uno
    menuItems.forEach(item => {
        const menuItem = document.createElement("div");
        menuItem.classList.add("menu-item"); // Agrega una clase CSS para dar estilo

        const title = document.createElement("span");
        title.textContent = item.name; // Establece el nombre del elemento del menú
        title.classList.add("card-title"); // Agrega una clase CSS para dar estilo

        const price = document.createElement("span");
        price.textContent = `${item.price}€`; // Establece el precio del elemento del menú
        price.classList.add("card-subtitle"); // Agrega una clase CSS para dar estilo

        const counter = document.createElement("span");
        counter.textContent = "0"; // Inicializa el contador en 0
        counter.classList.add("card-subtitle"); // Agrega una clase CSS para dar estilo

        const addButton = document.createElement("button");
        addButton.textContent = "+"; // Establece el texto del botón en "+"
        addButton.classList.add("green-button"); // Agrega una clase CSS para dar estilo
        addButton.addEventListener("click", function () {
            totalSum += item.price; // Aumenta el precio total
            totalDishes += 1; // Aumenta el número total de platos
            const currentCount = parseInt(counter.textContent) + 1; // Extrae el recuento actual
            counter.textContent = `${currentCount}`; // Actualiza el contador mostrado

           // Actualiza el objeto de platos seleccionados con cantidad y precio
            dishesSelected[item.name] = { quantity: currentCount, price: item.price };
            updateTotal(); // Actualiza la visualización total
        });

        const removeButton = document.createElement("button");
        removeButton.textContent = "-"; // Establece el texto del botón en "-"
        removeButton.classList.add("red-button"); // Agrega una clase CSS para dar estilo
        removeButton.addEventListener("click", function () {
            const currentCount = parseInt(counter.textContent); // Extrae el recuento actual
            if (currentCount > 0) {
                totalSum -= item.price; // Disminuye el precio total
                totalDishes -= 1; // Disminuye el número total de platos
                const newCount = currentCount - 1; // Calcula el nuevo recuento
                if (newCount === 0) {
                    delete dishesSelected[item.name]; // Elimina el elemento de los platos seleccionados si el recuento llega a 0
                } else {
                    dishesSelected[item.name] = { quantity: newCount, price: item.price }; // Actualiza los platos seleccionados
                }
                counter.textContent = `${newCount}`; // Actualiza el contador mostrado
                updateTotal(); // Actualiza la visualización total
            }
        });

        const buttonContainer = document.createElement("div");
        buttonContainer.classList.add("button-container"); // Agrega una clase CSS para dar estilo

        // Adjunta los elementos creados al contenedor del elemento del menú
        menuItem.appendChild(title);
        menuItem.appendChild(price);
        menuItem.appendChild(counter);
        productsSection.appendChild(menuItem);

        buttonContainer.appendChild(addButton);
        buttonContainer.appendChild(counter);
        buttonContainer.appendChild(removeButton);
        menuItem.appendChild(buttonContainer);
    });

    // Función para actualizar el precio total y la visualización de platos totales
    function updateTotal() {
        totalPriceElement.textContent = `Total Price: ${totalSum}€`;
        totalDishesElement.textContent = `Total Dishes: ${totalDishes}`;

        // Lanza un evento con los platos seleccionados actualizados
        const event = new CustomEvent('dishesUpdated', { detail: dishesSelected });
        document.dispatchEvent(event);

        console.log(dishesSelected); // Registra los platos seleccionados actualizados
    }
});
