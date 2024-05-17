function myFoodSearch() {
    // Declare variables
    var input, filter, ul, li, i, txtValue;
    input = document.getElementById('food-search-bar');
    filter = input.value.toUpperCase();
    ul = document.getElementById("food-list");
    li = ul.getElementsByTagName('li');
    
    // Loop through all list items, and hide those who don't match the search query
    for (i = 0; i < li.length; i++) {
      txtValue = li[i].textContent || li[i].innerText;
      if (txtValue.toUpperCase().indexOf(filter) > -1) {
        li[i].style.display = "";
      } else {
        li[i].style.display = "none";
      }
    }
}