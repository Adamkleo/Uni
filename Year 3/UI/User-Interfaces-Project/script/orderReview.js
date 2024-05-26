// Inicializar variables para rastrear la verificación del usuario y los platos seleccionados
let isUserVerified = false;
let dishesSelectedGlobal = {};

// Manejar el evento DOMContentLoaded
document.addEventListener("DOMContentLoaded", () => {
    const verifyButton = document.getElementById("verify-button");
  
    // Verificación del usuario al hacer clic
    verifyButton.addEventListener("click", () => {
        const userID = document.getElementById("user-id-input").value;
        const users = JSON.parse(localStorage.getItem("users")) || {};
        const user = users[userID];
    
        if (user) {
            alert("Verified! Order will be saved to your account.");
            isUserVerified = true;
            verifyButton.disabled = true;
        } else {
            alert("User not found, try again or continue as a guest.");
            document.getElementById("user-id-input").value = "";
        }
    });
  
    // Evento del botón de confirmación para guardar el pedido si el usuario está verificado
    document.getElementById("confirm-button").addEventListener("click", () => {
        if (isUserVerified) {
            const userID = document.getElementById("user-id-input").value;
            const users = JSON.parse(localStorage.getItem("users")) || {};
            users[userID].order_history.push(dishesSelectedGlobal);
            localStorage.setItem("users", JSON.stringify(users));
        }
    });
});

// Evento personalizado para actualizar los platos
document.addEventListener("dishesUpdated", (event) => {
    dishesSelectedGlobal = event.detail;
  
    const container = document.getElementById('orderReviewContainer');
    container.innerHTML = "";
  
    let totalSum = 0;
  
    // Iterar sobre los platos seleccionados para mostrarlos y calcular el total
    for (const [item, details] of Object.entries(dishesSelectedGlobal)) {
        const itemCost = details.quantity * details.price;
        totalSum += itemCost;
    
        const itemDiv = createItemDiv(item, details.quantity, itemCost);
        container.appendChild(itemDiv);
    }
  
    const totalDiv = document.createElement('div');
    totalDiv.className = 'total';
    totalDiv.innerHTML = `Total: €${totalSum}`;
    container.appendChild(totalDiv);
});

// Función para crear un div de elemento para la revisión del pedido
function createItemDiv(item, quantity, cost) {
    const itemDiv = document.createElement('div');
    itemDiv.className = 'item';
  
    const itemName = document.createElement('div');
    itemName.className = 'item-name';
    itemName.textContent = item;
  
    const itemQuantity = document.createElement('div');
    itemQuantity.className = 'item-quantity';
    itemQuantity.textContent = `${quantity}`;
  
    const itemPrice = document.createElement('div');
    itemPrice.className = 'item-price';
    itemPrice.textContent = `€${cost}`;
  
    itemDiv.appendChild(itemName);
    itemDiv.appendChild(itemQuantity);
    itemDiv.appendChild(itemPrice);
  
    return itemDiv;
}
