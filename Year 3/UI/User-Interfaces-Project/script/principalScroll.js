// Obtener todos los elementos con la clase "grid-item" y almacenarlos en 'items'
const items = document.querySelectorAll(".grid-item");

// Inicializar una variable para hacer un seguimiento de la sección actual
let currentSection = 0;

// Escuchar eventos de desplazamiento en la ventana
window.addEventListener("scroll", () => {
  // Obtener la posición actual de desplazamiento
  let scrollPos = window.scrollY;

  // Recorrer cada elemento para verificar si está actualmente en el área visible
  items.forEach((item, index) => {
    let offsetTop = item.offsetTop;
    let offsetBottom = offsetTop + item.offsetHeight;

    // Comprobar si el elemento actual está en el área visible
    if (scrollPos > offsetTop && scrollPos < offsetBottom) {
      // Comprobar si la sección actual ha cambiado
      if (currentSection !== index) {
        // Actualizar la sección actual
        currentSection = index;

        // Aplicar animación de escala y rotación al elemento actual.
        // Rotación alternada en función del índice.
        items[currentSection].style.transform = `scale(1.1) rotate(${index % 2 === 0 ? '3deg' : '-3deg'})`;
        items[currentSection].style.backgroundColor = "#f0f0f0";

        // Restablecer estilos para todos los demás elementos
        items.forEach((el, idx) => {
          if (idx !== currentSection) {
            el.style.transform = "scale(1) rotate(0deg)";
            el.style.backgroundColor = "initial";
          }
        });
      }
    }
  });
});
