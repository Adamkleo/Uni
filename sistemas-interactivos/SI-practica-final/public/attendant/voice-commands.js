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

    if (transcript.includes("accept")) {
        acceptOrder()
    }
    if (transcript.includes("reject")) {
        rejectOrder()
    }
}
