// Esperar hasta que el documento esté cargado
document.addEventListener("DOMContentLoaded", function () {

    // Sacar elemento formulario del HTML
    const form = document.querySelector('form');

    // Función para limpiar mensaje de validación personalizado
    const clearValidity = (input) => {
        input.setCustomValidity("");
    };

    // Obtener botón de cancelar por su id
    const cancelButton = document.getElementById('cancel-button');

    // Añadir eventlistener para botón de cancelar
    cancelButton.addEventListener('click', () => {
        window.location.href = 'nosotros.html'; // Redireccionar a nosotros.html
    });

    //Añadir event listeners para limpiar validación de cada formulario
    form.userID.addEventListener('input', () => clearValidity(form.userID));
    form.name.addEventListener('input', () => clearValidity(form.name));
    form.surname.addEventListener('input', () => clearValidity(form.surname));
    form.telephone.addEventListener('input', () => clearValidity(form.telephone));
    form.email.addEventListener('input', () => clearValidity(form.email));

    // Función para validar los campos del formulario
    const validateInput = (input, regex, message) => {
        if (!regex.test(input.value)) {
            input.setCustomValidity(message);
            input.reportValidity();
            return false;
        }
        return true;
    };

    // Event listener para entrega del formulario
    form.addEventListener('submit', (e) => {
        e.preventDefault(); // Prevenir comportamiento default de entrega de formulario

        // Fetch o inicializar data de usuarios de almacenamiento local
        let users = JSON.parse(localStorage.getItem('users')) || {};

        // Validar cada campo del formulario
        let isValidUserID = validateInput(form.userID, /^\d{8}[a-zA-Z]{1}$/, "Invalid userID format: 8 Digits, 1 Letter");
        let isValidName = validateInput(form.name, /^[a-zA-Z\s]+$/, "Invalid name format");
        let isValidSurname = validateInput(form.surname, /^[a-zA-Z\s]+$/, "Invalid surname format");
        let isValidTelephone = validateInput(form.telephone, /^\d{9}$/, "Invalid format: 9 digits required");
        let isValidEmail = validateInput(form.email, /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9-]+\.[a-zA-Z]{2,3}$/, "Invalid email format: Must be {}@{}.{}");

        // Comprobar si todos los campos son válidos
        if (isValidUserID && isValidName && isValidSurname && isValidTelephone && isValidEmail) {

            // Guardar información de usuario en almacenamiento local
            users[form.userID.value] = {
                name: form.name.value,
                surname: form.surname.value,
                telephone: form.telephone.value,
                email: form.email.value,
                password: form.password.value,
                order_history: []
            };

            // Guardar objeto de usuario actualizado
            localStorage.setItem('users', JSON.stringify(users));

            // Resetear el formulario
            form.reset();

            // Mostrar mensaje de éxito
            document.getElementById('form-submission').innerText = 'Success!';

            // Quitar mensaje después de 3 segundos
            setTimeout(() => {
                document.getElementById('form-submission').innerText = '';
            }, 3000);
        }
    });


});
