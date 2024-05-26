// Inicializa la visualización del temporizador y el círculo cuando el DOM se carga por completo
document.addEventListener("DOMContentLoaded", () => {
    const display = document.getElementById("timer");
    const progress = document.getElementById("progress");
    const totalLength = initCircle(progress);
    initTimerDisplay(display, '10:00');

    const confirmButton = document.getElementById("confirm-button");
    confirmButton.addEventListener("click", () => {
        startTimer(60 * 10, display, progress, totalLength);
    });
});

// Establece el texto inicial en la visualización del temporizador
function initTimerDisplay(display, initialText) {
    display.textContent = initialText;
}

// Inicializa el círculo y devuelve su longitud total
function initCircle(progress) {
    const totalLength = 2 * Math.PI * progress.r.baseVal.value;
    setCircleAttributes(progress, totalLength, totalLength);
    return totalLength;
}

// Establece los atributos del círculo para stroke-dasharray y stroke-dashoffset
function setCircleAttributes(progress, dashArray, dashOffset) {
    progress.setAttribute("stroke-dasharray", dashArray);
    progress.setAttribute("stroke-dashoffset", dashOffset);
}

// Formatea el tiempo en minutos y segundos
function formatTime(minutes, seconds) {
    return `${minutes}:${seconds < 10 ? '0' + seconds : seconds}`;
}

// Inicia el temporizador y actualiza la visualización y el círculo
function startTimer(duration, display, progress, totalLength) {
    document.body.classList.add('timer-active');
    let timer = duration, minutes, seconds;

    const interval = setInterval(() => {
        minutes = parseInt(timer / 60, 10);
        seconds = parseInt(timer % 60, 10);

        // Actualiza la visualización del temporizador
        display.textContent = formatTime(minutes, seconds);

        // Actualiza el círculo de progreso
        const offset = (timer / duration) * totalLength;
        setCircleAttributes(progress, totalLength, totalLength - offset);

        // Detén el temporizador cuando llegue a 0
        if (--timer < 0) {
            clearInterval(interval);
            document.getElementById("status-message").textContent = 'Order arrived';
            initTimerDisplay(display, '');
            document.body.classList.remove('timer-active');
        }
    }, 1000);
}
