// Utilizar cuando el DOM esté completamente cargado
document.addEventListener("DOMContentLoaded", () => {
    const productItem = document.getElementById("product-item");
    const reviewItem = document.getElementById("review-item");

    const continueButton = document.getElementById("continue-button");
    const confirmButton = document.getElementById("confirm-button");

    const productsSection = document.getElementById("products-section");
    const reviewSection = document.getElementById("review-section");
    const statusSection = document.getElementById("status-section");

    let currentSection = productsSection;

    // Inicializar botones
    continueButton.disabled = true;
    confirmButton.style.display = 'none';

    // Alternar entre secciones activas y no activas
    function toggleSection(showSection, hideSections, completedItems, incompleteItems) {
        showSection.classList.add("active");
        hideSections.forEach(section => section.classList.remove("active"));
        completedItems.forEach(item => item.classList.add("completed"));
        incompleteItems.forEach(item => item.classList.remove("completed"));
        currentSection = showSection;
    }

    // Escuchas de eventos para elementos de navegación
    productItem.addEventListener("click", () => {
        if (currentSection !== statusSection) {
            toggleSection(productsSection, [reviewSection, statusSection], [], [productItem, reviewItem]);
        }
    });

    reviewItem.addEventListener("click", () => {
        if (currentSection !== statusSection) {
            toggleSection(reviewSection, [productsSection, statusSection], [productItem], [reviewItem]);
        }
    });

    // Event listener para moverse a la sección de revisión
    continueButton.addEventListener("click", () => {
        if (currentSection === productsSection) {
            toggleSection(reviewSection, [productsSection, statusSection], [productItem], [reviewItem]);
            confirmButton.style.display = 'inline-block';
        }
    });

    // Event listener para moverse a la sección de estado
    confirmButton.addEventListener("click", () => {
        if (currentSection === reviewSection) {
            toggleSection(statusSection, [productsSection, reviewSection], [productItem, reviewItem], []);
        }
    });

    // Event listener para habilitar/deshabilitar el botón de continuar basado en los platos seleccionados
    document.addEventListener("dishesUpdated", function(event) {
        const dishesSelected = event.detail;
        const totalDishes = Object.values(dishesSelected).reduce((sum, dish) => sum + dish.quantity, 0);
        continueButton.disabled = totalDishes <= 0;
    });
});
