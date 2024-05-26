function filterAlimentos() {
  var checkboxes = document.querySelectorAll(
    '.food-filter-container input[type="checkbox"]'
  );

  // Filtrar los elementos de la lista
  checkboxes.forEach(function (checkbox) {
    checkbox.addEventListener("change", function () {
      var filterClass = checkbox.id.replace("-check", "");

      // Mostrar u ocultar elementos según el estado del checkbox
      var foodItems = document.querySelectorAll(".food-item." + filterClass);
      foodItems.forEach(function (item) {
        if (checkbox.checked) {
          item.classList.add("filtered");
        } else {
          item.classList.remove("filtered");
        }
      });
    });
  });
}
