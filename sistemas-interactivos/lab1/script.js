let map;
let currentLat, currentLng;
let destinationLat, destinationLng;
let userLocationMarker;
let distanceThreshold
let alerted = false

function initMap(lat, lng) {
    map = L.map('map').setView([lat, lng], 13);
    L.tileLayer('https://tile.openstreetmap.org/{z}/{x}/{y}.png', {}).addTo(map);
    L.marker([lat, lng]).addTo(map).bindPopup('You are here!').openPopup();
    map.on('click', onMapClick);

    var customControl = L.Control.extend({
        options: {
            position: 'topleft'
        },
        onAdd: function (map) {
            var container = L.DomUtil.create('div', 'leaflet-bar leaflet-control leaflet-control-custom');
            container.style.backgroundColor = 'white';
            container.style.padding = '10px';
            container.style.boxShadow = '0 0 5px rgba(0,0,0,0.5)';
            container.style.borderRadius = '10px'
            container.innerHTML = `
            <button id="toggleButton">+</button>
            <div id="infoPanel" style="display: none; font-size: 14px;">
                <div id="distance">Distance Remaining: </div>
            </div>
            `;
            L.DomEvent.disableClickPropagation(container);


            container.querySelector('#toggleButton').onclick = function() {
                var infoPanel = container.querySelector('#infoPanel');
                if (infoPanel.style.display === 'none') {
                    infoPanel.style.display = 'block';
                } else {
                    infoPanel.style.display = 'none';
                }
            };

            return container;
        }
    });
    
    map.addControl(new customControl());
}



function onMapClick(e) {
    destinationLat = e.latlng.lat;
    destinationLng = e.latlng.lng;
    console.log(distanceThreshold)

    if (window.currentMarker) {
        map.removeLayer(window.currentMarker);
    }

    window.currentMarker = L.marker(e.latlng, {draggable: true}).addTo(map);
    let popupContent = `<p style="font-size: 14px;">Your destination</p><button class="delete-btn" onclick="removeCurrentMarker()">Remove</button>`;
    window.currentMarker.bindPopup(popupContent).openPopup();

    window.currentMarker.on('dragend', function(event) {
        var marker = event.target;
        var position = marker.getLatLng();

        destinationLat = position.lat;
        destinationLng = position.lng;

        updateInformation(); 
    });

    updateInformation();
}

function removeCurrentMarker() {
    if (window.currentMarker) {
        map.removeLayer(window.currentMarker);
        window.currentMarker = null;

        destinationLat = undefined;
        destinationLng = undefined;

        document.getElementById('destination').textContent = "Destination: ";


        const distanceText = "Distance: "; 
        document.getElementById('distance').textContent = distanceText; 
        var infoPanelDistance = document.querySelector('#infoPanel #distance');
        if (infoPanelDistance) { 
            infoPanelDistance.textContent = distanceText; 
        }

        updateInformation(); 
    }
}


function updateUserLocation(lat, lng) {
    currentLat = lat;
    currentLng = lng;
    if (!userLocationMarker) {
        userLocationMarker = L.marker([lat, lng], {title: "You are here!"}).addTo(map).bindPopup('You are here!').openPopup();
    } else {
        userLocationMarker.setLatLng([lat, lng]);
        if (!userLocationMarker.getPopup().isOpen()) {
            userLocationMarker.getPopup().setContent('You are here!').openPopup();
        }
    }
    updateInformation();
}


document.addEventListener('DOMContentLoaded', function() {
    navigator.geolocation.watchPosition(position => {
        if (!map) {
            initMap(position.coords.latitude, position.coords.longitude);
        }
        updateUserLocation(position.coords.latitude, position.coords.longitude);
    }, err => {
        console.error(`Error: ${err.message}`);
    }, {
        enableHighAccuracy: true,
        maximumAge: 0,
        timeout: Infinity
    });
});



function updateInformation() {
    if(currentLat !== undefined && currentLng !== undefined) {
        document.getElementById('location').textContent = `Current Location: ${currentLat.toFixed(3)}, ${currentLng.toFixed(3)}`;
    }
    if(destinationLat !== undefined && destinationLng !== undefined) {
        document.getElementById('destination').textContent = `Destination: ${destinationLat.toFixed(3)}, ${destinationLng.toFixed(3)}`;
    }
    if(currentLat !== undefined && currentLng !== undefined && destinationLat !== undefined && destinationLng !== undefined) {
        const dist = calculateDistance(currentLat, currentLng, destinationLat, destinationLng);
        
        const distanceText = `Distance: ${dist.toFixed(2)} km`;
        document.getElementById('distance').textContent = distanceText; 
        
        var infoPanelDistance = document.querySelector('#infoPanel #distance');
        if (infoPanelDistance) { 
            infoPanelDistance.textContent = distanceText;
        }
        if (dist < distanceThreshold) { 
            
            navigator.vibrate(1000); 
            if (!alerted) {
                alert("You are approaching your destination!")
                alerted = true
            }
        }
    }
}


let slider = document.getElementById("myRange");
let output = document.getElementById("demo");
output.innerHTML = slider.value;

slider.oninput = function() {
  output.innerHTML = (this.value * 0.1).toFixed(1);
  distanceThreshold = output.innerHTML
}