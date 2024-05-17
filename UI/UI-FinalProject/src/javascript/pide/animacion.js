function startDeliveryAnimation(duration) {
    const movingShape = document.getElementById('moving-shape');
    const timerElement = document.getElementById('delivery-timer');
    let timer = duration;
    let paused = false;
  
    const interval = setInterval(function() {
      if (!paused) {
        timer--;
      }
  
      let minutes = Math.floor(timer / 60);
      let seconds = timer % 60;
      timerElement.textContent = minutes.toString().padStart(2, '0') + ':' + seconds.toString().padStart(2, '0');
  
      let progress = ((duration - timer) / duration) * 100;
      movingShape.style.left = `${progress}%`;
  
      if (progress >= 50 && progress < 52 && !paused) { 
        paused = true;
        setTimeout(() => { paused = false; }, 2000); 
      }
  
      if (timer <= 0) {
        clearInterval(interval);
        movingShape.style.left = '100%';
      }
    }, 1000);
  }
  
  startDeliveryAnimation(120); 
