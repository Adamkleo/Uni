document.addEventListener('DOMContentLoaded', function () {
    var galleryImages = document.querySelectorAll('.gallery-image');
    var currentIndex = 0; // Start with the first image as the active one


    function updateImageName(newIndex) {
        var imageNameElement = document.querySelector('.image-name');
        var imageName = galleryImages[newIndex].getAttribute('alt'); // Get the alt text of the new active image
        imageNameElement.textContent = imageName; // Set the text content of the placeholder to the alt text
    }
    // Function to update the gallery to the new state
    function updateGallery(newIndex) {
        // Remove all classes first
        galleryImages.forEach(function (image) {
            image.classList.remove('prev', 'active', 'next');
        });

        // Calculate the index for previous, current, and next images
        var prevIndex = newIndex - 1 < 0 ? galleryImages.length - 1 : newIndex - 1;
        var nextIndex = (newIndex + 1) % galleryImages.length;

        // Assign the new classes to the images
        galleryImages[prevIndex].classList.add('prev');
        galleryImages[newIndex].classList.add('active');
        galleryImages[nextIndex].classList.add('next');

        // Update the current index
        currentIndex = newIndex;
        updateImageName(newIndex); // Call this function to update the image name

    }

    // Set up the automatic gallery rotation
    var autoRotate = setInterval(function () {
        var newIndex = (currentIndex + 1) % galleryImages.length;
        updateGallery(newIndex);
    }, 2500); // Change image every 5 seconds

    // Set up click events for manual navigation
    document.querySelector('.gallery').addEventListener('click', function (e) {
        // Check if the clicked element is one of the navigation images
        if (e.target.classList.contains('prev')) {
            // Show the previous image
            var newIndex = currentIndex - 1 < 0 ? galleryImages.length - 1 : currentIndex - 1;
            updateGallery(newIndex);
        } else if (e.target.classList.contains('next')) {
            // Show the next image
            var newIndex = (currentIndex + 1) % galleryImages.length;
            updateGallery(newIndex);
        }

        // Reset the timer for automatic rotation when manually navigating
        clearInterval(autoRotate);
        autoRotate = setInterval(function () {
            var newIndex = (currentIndex + 1) % galleryImages.length;
            updateGallery(newIndex);
        }, 5000);
    });
});
