document.addEventListener("DOMContentLoaded", function() {
    const reservationForm = document.getElementById('reservationForm');

    reservationForm.addEventListener("submit", confirmarReserva);


    function confirmarReserva(event) {
        event.preventDefault();
        const reservationName = document.getElementById('reservationName').value;
        const reservationDate = document.getElementById('reservationDate').value;
        const reservationTime = document.getElementById('reservationTime').value;
        const numberOfPeople = document.getElementById('numberOfPeople').value;

        if (!reservationName || !reservationDate || !reservationTime || !numberOfPeople) {
            alert("Por favor completa todos los campos para la reserva.");
            return;
        }

        if (isAlreadyReserved(reservationName)) {
            alert("Ya existe una reserva a nombre de " + reservationName + ".");
            return;
        }

        let confirmar = confirm("¿Quiere confirmar la reserva para " + reservationName + " el " + reservationDate + " a las " + reservationTime + " para " + numberOfPeople + " personas?");
        if (confirmar) {
            storeReservation(reservationName, reservationDate, reservationTime, numberOfPeople);
            alert("Reserva confirmada");
        }
    }

    function isAlreadyReserved(name) {
        let reservations = JSON.parse(localStorage.getItem('reservations')) || [];
        return reservations.some(reservation => reservation.name === name);
    }

    function storeReservation(name, date, time, numberOfPeople) {
        let reservations = JSON.parse(localStorage.getItem('reservations')) || [];
        reservations.push({ name, date, time, numberOfPeople });
        localStorage.setItem('reservations', JSON.stringify(reservations));
    }


});