function showNextMenu(currentMenu) {
  var current = document.getElementById(currentMenu);
  if (currentMenu == "seleccion") {
    var next = document.getElementById("revision");
    mostrarRevision();
    document.getElementById("step-list-seleccion").classList.toggle("active");
    document.getElementById("step-list-revision").classList.toggle("active");
  } else if (currentMenu == "revision") {
    var next = document.getElementById("estado");
    document.getElementById("step-list-revision").classList.toggle("active");
    document.getElementById("step-list-estado").classList.toggle("active");
  }
  current.classList.toggle("hidden");
  next.classList.toggle("hidden");
}

function showPreviousMenu(currentMenu) {
  var current = document.getElementById(currentMenu);
  if (currentMenu == "revision") {
    var prev = document.getElementById("seleccion");
    document.getElementById("step-list-revision").classList.toggle("active");
    document.getElementById("step-list-seleccion").classList.toggle("active");
  } else if (currentMenu == "estado") {
    var prev = document.getElementById("revision");
    document.getElementById("step-list-estado").classList.toggle("active");
    document.getElementById("step-list-revision").classList.toggle("active");
  }
  current.classList.toggle("hidden");
  prev.classList.toggle("hidden");
}

function mostrarRevision() {
  const lista_revision = document.getElementById("revision-resumen");
  /* Primero limpiamos la lista anterior */
  while (lista_revision.firstChild) {
    lista_revision.removeChild(lista_revision.firstChild);
  }

  /* Añadimos los valores actuales de la lista de foods */
  var myFoodRecuperadosString = localStorage.getItem("myFood");
  console.log(myFoodRecuperadosString);
  var myFoodRecuperados = JSON.parse(myFoodRecuperadosString);
  for (const food in myFoodRecuperados) {
    if (myFoodRecuperados[food] != 0) {
      /* crea elementos seleccionados con su precio */
      const listItem = document.createElement("li");
      const ItemPrecio = document.createElement("span");
      /* añade contenido */
      listItem.textContent = `x${myFoodRecuperados[food]} - ${food}`;
      ItemPrecio.textContent = ` ${myFoodPrices[food]} €`;
      /* añade al elemento correspondiente */
      lista_revision.appendChild(listItem);
      listItem.appendChild(ItemPrecio);
    }
  }
}

/* prettier-ignore */
myFoodPrices = {
  "sushi-maki": 9.00,
  "ramen": 10.00,
  "donburi": 9.50,
  "tempura": 7.50,
  "ensalada": 6.00,
  "gyozas": 7.00,
  "bento": 12.00,
  "takoyaki": 8.00,
  "edamame": 5.00,
  "helado": 4.50
};
