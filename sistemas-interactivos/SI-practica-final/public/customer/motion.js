
const shakeThreshold = 15;
let lastX = null, lastY = null, lastZ = null;

function handleMotionEvent(e) {
    let { x, y, z } = e.accelerationIncludingGravity;

    if (lastX !== null && lastY !== null && lastZ !== null) {
        let deltaX = Math.abs(lastX - x);
        let deltaY = Math.abs(lastY - y);
        let deltaZ = Math.abs(lastZ - z);

        if ((deltaX > shakeThreshold && deltaY > shakeThreshold) || 
            (deltaX > shakeThreshold && deltaZ > shakeThreshold) || 
            (deltaY > shakeThreshold && deltaZ > shakeThreshold)) {
            console.log('Shake detected');
            
            sortProductsByCount();
        }
    }

    lastX = x;
    lastY = y;
    lastZ = z;
}

if (typeof DeviceMotionEvent.requestPermission === 'function') {
    
    DeviceMotionEvent.requestPermission().then(permissionState => {
        if (permissionState === 'granted') {
            window.addEventListener('devicemotion', handleMotionEvent);
        } else {
            console.error('Permission to use motion sensor was denied.');
        }
    }).catch(console.error);
} else {
    
    window.addEventListener('devicemotion', handleMotionEvent);
}
