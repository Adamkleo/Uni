document.getElementById('contactForm').addEventListener('submit', function(event) {
    event.preventDefault();

    var name = document.getElementById('name').value;
    var email = document.getElementById('email').value;
    var message = document.getElementById('message').value;

    // Regular expression for basic email validation
    var emailRegex = /^[a-zA-Z0-9._-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;

    // Regular expression for basic name validation (adjust as needed)
    var nameRegex = /^[a-zA-Z ]{2,30}$/;

    if (!nameRegex.test(name)) {
        alert('Please enter a valid name.');
        return;
    }

    if (!emailRegex.test(email)) {
        alert('Please enter a valid email address.');
        return;
    }

    if (!message) {
        alert('Please enter a message.');
        return;
    }

    // Add your form submission logic here (e.g., send data to a server)
    alert('Form submitted successfully!');

    // Reset the form after successful submission
    document.getElementById('contactForm').reset();
});
