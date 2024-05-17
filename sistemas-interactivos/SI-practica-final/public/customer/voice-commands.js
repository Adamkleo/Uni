let recognition;
let isListening = false;  

function setupVoiceCommands() {
    try {
        const SpeechRecognition = window.SpeechRecognition || window.webkitSpeechRecognition;
        recognition = new SpeechRecognition();
        recognition.lang = 'en-US';
        recognition.continuous = true;  
        recognition.interimResults = false;  
        recognition.maxAlternatives = 1;

        recognition.onresult = function (event) {
            const transcript = event.results[event.resultIndex][0].transcript.trim().toLowerCase();
            console.log('Heard:', transcript);  
            handleCommands(transcript);  
        };

        recognition.onend = function () {
            if (isListening) {  
                recognition.start();
            }
        };

        recognition.onerror = function (event) {
            console.error('Speech Recognition Error:', event.error);
        };
    } catch (error) {
        console.error('Speech Recognition is not supported by this browser:', error);
    }
}

function toggleSpeechRecognition() {
    if (!recognition) {
        setupVoiceCommands();  
    }
    let voiceButton = document.querySelector('.nav-button.voice');  

    if (isListening) {
        recognition.stop();
        isListening = false;
        voiceButton.classList.remove('active');
        console.log("Speech recognition stopped.");
    } else {
        recognition.start();
        isListening = true;
        voiceButton.classList.add('active');
        console.log("Speech recognition started, speak now...");
    }
}

function handleCommands(transcript) {
    let checkout = false;

    if (transcript.includes("checkout") || transcript.includes("check out") || transcript.includes("go to checkout") || transcript.includes("go to check out") || transcript.includes("proceed to checkout") || transcript.includes("proceed to check out") || transcript.includes("go to payment") || transcript.includes("go to payment page")) {
        toggleView('checkout');
        checkout = true;
    } else if (transcript.includes("return") || transcript.includes("back") || transcript.includes("shop") || transcript.includes("go back") || transcript.includes("go to shop") || transcript.includes("go to store")) {
        toggleView('shop');
        checkout = false;
    } else if (transcript.includes("favorites") || transcript.includes("go to favorites") || transcript.includes("favourites") || transcript.includes("go to favourites")) {
        toggleView('favorites');
        checkout = false;
    } else if (transcript.includes("sort") || transcript.includes("arrange") || transcript.includes("test")) {
        sortProductsByCount();
        checkout = false;
    } else if (transcript.includes("purchase") || transcript.includes("finalize") || transcript.includes("complete") || transcript.includes("finish") || transcript.includes("buy") || transcript.includes("place order") || transcript.includes("place the order") || transcript.includes("confirm order") || transcript.includes("confirm the order")) {
        finalizePurchase();  
    }

}
