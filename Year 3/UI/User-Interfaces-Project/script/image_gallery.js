//Indice default es 1
let indice=1;
mostrar(indice);
//La función cambiar_imagen se activa al pulsar en las flechas
function cambiar_imagen(i){
    mostrar(indice+=i);
}
//La función imagen_actual se activa al pulsar en los círculos
function imagen_actual(i){
    mostrar(indice=i);
}

function mostrar(i){
    let j;
    //Obtener elementos "diapositivas" y "circulo"
    let imgs=document.getElementsByClassName("diapositivas");
    let circulos=document.getElementsByClassName("circulo");
    //Si se hace click en la fecha estando en la última imagen se volverá a la primera imagen
    if (i>imgs.length){
        indice=1};
    //Si se hace click en la flecha de la izquierda estando en la primera imagen se volverá a la última imagen
        if (i<1){
        indice=imgs.length;
    }
    //Ocultar todas las imágenes
    for(j=0;j<imgs.length;j++){
        imgs[j].style.display="none";
    }
    //Establecer todos los círculos como no activo
    for(j=0;j<circulos.length;j++){
        circulos[j].classList.remove("active");
    }
    //Mostrar solo la imagen en la que se está
    imgs[indice-1].style.display="block";
    //Añadir el atributo active al círculo que corresponde a la imagen actual
    circulos[indice-1].className+=" active";
}