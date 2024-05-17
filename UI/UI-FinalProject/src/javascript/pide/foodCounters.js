// Obtiene todos los elementos de contador y botones

let counters = document.getElementsByClassName("counter");
let incremenButtons = document.getElementsByClassName("increment");
for (let i = 0; i < incremenButtons.length; i++) {
  
  incremenButtons[i].addEventListener("click", function () {
    counters[i].textContent = parseInt(counters[i].textContent) + 1;
  });
}


let decrementButtons = document.getElementsByClassName("decrement");
for (let i = 0; i < decrementButtons.length; i++) {
  
  decrementButtons[i].addEventListener("click", function () {
    if (counters[i].textContent > 0) {
      counters[i].textContent = parseInt(counters[i].textContent) - 1;
    }
  });
}

var myFood = {};

let myFoodString = JSON.stringify(myFood);
localStorage.setItem("myFood", myFoodString);

function updateMasterCounter() {
  var myFoodRecuperadosString = localStorage.getItem("myFood");
  var myFoodRecuperados = JSON.parse(myFoodRecuperadosString);
  var totalCount = 0;

  for (var food in myFoodRecuperados) {
    totalCount += myFoodRecuperados[food];
  }

  document.getElementById("master-counter").textContent = totalCount;

  var nextPageButton = document.getElementById("nextButtonSeleccion");
  if (totalCount > 0) {
    nextPageButton.disabled = false;
  } else {
    nextPageButton.disabled = true;
  }
}

updateMasterCounter();
function addFood(food_name) {
  var myFoodRecuperadosString = localStorage.getItem("myFood");
  localStorage.removeItem("myFood");

  var myFoodRecuperados = JSON.parse(myFoodRecuperadosString);

  if (!myFoodRecuperados[food_name]) {
    myFoodRecuperados[food_name] = 1;
  } else {
    myFoodRecuperados[food_name] += 1;
  }

  var myNewFoodString = JSON.stringify(myFoodRecuperados);
  localStorage.setItem("myFood", myNewFoodString);
  updateMasterCounter(); 
}

function removeFood(food_name) {
  var myFoodRecuperadosString = localStorage.getItem("myFood");
  localStorage.removeItem("myFood");

  var myFoodRecuperados = JSON.parse(myFoodRecuperadosString);
  if (myFoodRecuperados[food_name] > 0) {
    myFoodRecuperados[food_name] -= 1;
  }

  var myFoodString = JSON.stringify(myFoodRecuperados);
  localStorage.setItem("myFood", myFoodString);
  updateMasterCounter(); 
}
