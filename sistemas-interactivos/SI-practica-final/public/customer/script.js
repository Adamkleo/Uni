let index_active_camera = 1;
let available_cameras = [];
let scanner = new Instascan.Scanner({ video: document.getElementById('preview') });
let products = [
    {'id': 1, 'name': 'Manzanas', 'image': '../assets/products/manzanas.png', 'qrCode': '../assets/QR/manzanas.png', 'count': 0, 'price': 0.9}, 
    {'id': 2, 'name': 'Naranjas', 'image': '../assets/products/naranjas.jpg', 'qrCode': '../assets/QR/naranjas.png', 'count': 0, 'price': 1.2}, 
    {'id': 3, 'name': 'Platanos', 'image': '../assets/products/platanos.jpg', 'qrCode': '../assets/QR/platanos.png', 'count': 0, 'price': 0.8}, 
    {'id': 4, 'name': 'Huevos', 'image': '../assets/products/huevos.jpg', 'qrCode': '../assets/QR/huevos.png', 'count': 0, 'price': 2}, 
    {'id': 5, 'name': 'Leche', 'image': '../assets/products/leche.jpg', 'qrCode': '../assets/QR/leche.png', 'count': 0, 'price': 1}, 
    {'id': 6, 'name': 'Pan', 'image': '../assets/products/pan.jpg', 'qrCode': '../assets/QR/pan.png', 'count': 0, 'price': 0.7}, 
    {'id': 7, 'name': 'Pechuga de Pollo', 'image': '../assets/products/pollo.jpg', 'qrCode': '../assets/QR/pechuga de pollo.png', 'count': 0, 'price': 4},
    {'id': 8, 'name': 'Carne', 'image': '../assets/products/carne.jpg', 'qrCode': '../assets/QR/carne.png', 'count': 0, 'price': 5}, 
    {'id': 9, 'name': 'Salmon', 'image': '../assets/products/salmon.jpg', 'qrCode': '../assets/QR/salmon.png', 'count': 0, 'price': 8}, 
    {'id': 10, 'name': 'Arroz', 'image': '../assets/products/arroz.jpg', 'qrCode': '../assets/QR/arroz.png', 'count': 0, 'price': 1}, 
    {'id': 11, 'name': 'Pasta', 'image': '../assets/products/pasta.jpg', 'qrCode': '../assets/QR/pasta.png', 'count': 0, 'price': 1.1}, 
    {'id': 12, 'name': 'Tomates', 'image': '../assets/products/tomates.jpg', 'qrCode': '../assets/QR/tomates.png', 'count': 0, 'price': 0.5}, 
    {'id': 13, 'name': 'Cebollas', 'image': '../assets/products/cebollas.jpg', 'qrCode': '../assets/QR/cebollas.png', 'count': 0, 'price': 0.8}, 
    {'id': 14, 'name': 'Lechuga', 'image': '../assets/products/lechuga.jpg', 'qrCode': '../assets/QR/lechuga.png', 'count': 0, 'price': 1}, 
    {'id': 15, 'name': 'Queso', 'image': '../assets/products/queso.jpg', 'qrCode': '../assets/QR/queso.png', 'count': 0, 'price': 3}, 
    {'id': 16, 'name': 'Mantequilla', 'image': '../assets/products/mantequilla.jpg', 'qrCode': '../assets/QR/mantequilla.png', 'count': 0, 'price': 2}, 
    {'id': 17, 'name': 'Yogur', 'image': '../assets/products/yogur.jpg', 'qrCode': '../assets/QR/yogur.png', 'count': 0, 'price': 1.3}, 
    {'id': 18, 'name': 'Cafe', 'image': '../assets/products/cafe.jpg', 'qrCode': '../assets/QR/cafe.png', 'count': 0, 'price': 3.5}, 
    {'id': 19, 'name': 'Te', 'image': '../assets/products/te.jpg', 'qrCode': '../assets/QR/te.png', 'count': 0, 'price': 2}, 
    {'id': 20, 'name': 'Chocolate', 'image': '../assets/products/chocolate.jpg', 'qrCode': '../assets/QR/chocolate.png', 'count': 0, 'price': 2}
]

let favorites = [];




function start_scanner(camera) {

    scanner.stop();
    scanner.start(camera);
}

function switch_camera() {
    if (available_cameras.length > 1) {
        index_active_camera = (index_active_camera + 1) % available_cameras.length;
        let active_camera = available_cameras[index_active_camera];
        start_scanner(active_camera);
    }
}

Instascan.Camera.getCameras().then(function (cameras) {
    if (cameras.length > 0) {
        available_cameras = cameras;

        scanner.start(cameras[index_active_camera]);

        document.getElementById("switch_camera").addEventListener('touchend', switch_camera);
    }
    else {
        console.error("No cameras found");
    }
}).catch(function (e) {
    console.error(e);
});

function find_element(array, name) {
    return array.find(product => product.name === name);
}

scanner.addListener('scan', function (content) {
    let product = products.find(p => p.name === content);
    if (product) {
        product.count++;
        updateProductDisplay(product);
        updateCartDisplay();
    } else {
        console.error('Scanned product not found:', content);
    }
});

function updateProductDisplay(product) {
    const countSpan = document.getElementById(`count-${product.id}`);
    if (countSpan) {
        countSpan.textContent = product.count;
    }
}

function updateCartDisplay() {
    const checkoutItems = document.getElementById('checkout-items');
    checkoutItems.innerHTML = ''; 
    products.filter(p => p.count > 0).forEach(product => {
        const checkoutItem = document.createElement('div');
        checkoutItem.className = 'checkout-item';
        checkoutItem.innerHTML = `<img src="../assets/products/${product.image}" alt="${product.name}" class="checkout-image">
            <div>${product.name}</div>
            <div>Quantity: ${product.count}</div>`;
        checkoutItems.appendChild(checkoutItem);
    });
}


document.addEventListener('DOMContentLoaded', function () {
    var socket = io();  

    socket.on('connect', function () {
        console.log('Connected to server');
    });

    socket.on('productAdded', handleNewProduct);  

    socket.on('disconnect', function (reason) {
        console.log('Disconnected: ', reason);
        if (reason === 'io server disconnect') {
            socket.connect();
        }
    });

    const cartItems = document.getElementById('cart-items');
    loadProducts(products, cartItems);
    updateTotalPriceDisplay();  

    window.products = products; 
});

function toggleView(view) {
    const allPages = document.querySelectorAll('.page');
    allPages.forEach(page => {
        if (page.id === view) {
            page.style.display = 'block';
        } else {
            page.style.display = 'none';
        }
    });

    if (view === 'checkout') {
        displayCheckoutItems();
    } else if (view === 'favorite') {
        updateFavoritesDisplay();
    }
}



function loadProducts(products, container) {
    products.forEach(product => {
        const item = createProductItem(product);
        container.appendChild(item);
        setupTouchControls(item, product);
    });
}

function createProductItem(product) {

    const item = document.createElement('div');
    item.className = 'product-item';
    item.id=`product-item-${product.id}`;
    item.innerHTML = `<img src="${product.image}" alt="${product.name}" class="product-image">
        <div class="product-name">${product.name}</div>
        <div class="product-price">${product.price} €</div>
        <div class="product-count"><span class="counter" id="count-${product.id}">0</span></div>`;
    return item;
}

function setupTouchControls(item, product) {
    let touchStartX = 0;
    let touchEndX = 0;
    let touchStartY = 0;
    let touchEndY = 0;
    let touchStartTime = 0;
    item.addEventListener('touchstart', function (event) {
        touchStartX = event.touches[0].clientX;
        touchStartY = event.touches[0].clientY;
        touchStartTime = new Date().getTime();
        event.preventDefault();  
    }, false);

    item.addEventListener('touchend', function (event) {
        touchEndX = event.changedTouches[0].clientX;
        touchEndY = event.changedTouches[0].clientY;
        let touchDuration = new Date().getTime() - touchStartTime;
                handleGesture(item, product, touchStartX, touchEndX, touchStartY, touchEndY, touchDuration);
    }, false);
}

function handleGesture(item, product, startX, endX, startY, endY, duration) {
    const xDiff = endX - startX;
    const yDiff = endY - startY;

    if (Math.abs(xDiff) > Math.abs(yDiff)) {  
        if (xDiff > 50) {  
            modifyCount(item, product, 1);
        } else if (xDiff < -50) {  
            modifyCount(item, product, -1);
        }
    } else {
        if (Math.abs(xDiff) < 10 && Math.abs(yDiff) < 10 && duration > 1000) {  
            
            navigator.vibrate(1000);
            toggleFavorite(product);
        }
    }
}


function modifyCount(item, product, change) {
    product.count += change;
    if (product.count < 0) product.count = 0;
    const countSpan = document.getElementById(`count-${product.id}`);
    countSpan.textContent = product.count;
    if (product.isFavorite) {
        updateFavoritesDisplay(); 
    }
    updateTotalPriceDisplay();
    displayCheckoutItems(); 
}

function displayCheckoutItems() {
    const checkoutItems = document.getElementById('checkout-items');
    checkoutItems.innerHTML = ''; 
    window.products.forEach(product => {
        if (product.count > 0) {
            const checkoutItem = document.createElement('div');
            checkoutItem.className = 'checkout-item';
            checkoutItem.innerHTML = `<img src="${product.image}" alt="${product.name}" class="checkout-image">
                <div class="product-name">${product.name}</div>
                <div class="product-price">${product.price} €</div>
                <div>Quantity: ${product.count}</div>`;
            checkoutItems.appendChild(checkoutItem);
        }
    });
}




function toggleCameraView() {
    var scannerElement = document.getElementById('qr_scanner');
    if (scannerElement.style.display === 'none') {
        scannerElement.style.display = 'block';  
        startScanner(available_cameras[index_active_camera]); 
    } else {
        scannerElement.style.display = 'none';  
        scanner.stop();  
    }
}

function startScanner(camera) {
    scanner.stop();  
    scanner.start(camera);  
}



function toggleFavorite(product) {
        const item = document.getElementById(`product-item-${product.id}`);
        const index = favorites.findIndex(p => p.id === product.id);
    if (index > -1) {
        favorites.splice(index, 1);
        item.classList.remove('favorite');
    } else {
                favorites.push(product);
        item.classList.add('favorite');
            }
    
    updateFavoritesDisplay();
    displayCheckoutItems();  
}



function updateFavoritesDisplay() {
        const favoritesContainer = document.getElementById('favorite-items');
    favoritesContainer.innerHTML = ''; 
    favorites.forEach(product => {
        const favoriteItem = document.createElement('div');
        favoriteItem.className = 'favorite-item'; 
        favoriteItem.innerHTML = `
            <img src="${product.image}" alt="${product.name}" class="product-image">
            <div class="favorite-name">${product.name}</div>
        `; 
        favoritesContainer.appendChild(favoriteItem);
    });
}





function sortProductsByCount() {
    products.sort((a, b) => b.count - a.count);
    renderProducts(products); 
}



function renderProducts(products) {
    const container = document.getElementById('cart-items');
    container.innerHTML = '';  

    products.forEach(product => {
        const item = document.createElement('div');
        item.className = 'product-item';
        item.id = `product-item-${product.id}`;  
        item.innerHTML = `
            <img src="${product.image}" alt="${product.name}" class="product-image">
            <div class="product-name">${product.name}</div>
            <div class="product-price">${product.price} €</div>
            <div class="product-count"><span id="count-${product.id}">${product.count}</span></div>
        `; 
                container.appendChild(item);
        setupTouchControls(item, product);  
    });
}



function handleNewProduct(productDetails) {
    
    const newProduct = {
        id: products.length + 1,  
        name: productDetails.name,
        image: productDetails.image,
        qrCode: '',  
        count: 0,  
        price: productDetails.price
    };

    
    products.push(newProduct);

    
    renderProducts(products);
    updateTotalPriceDisplay();  

    console.log(products)
}



function calculateTotalPrice() {
    let totalPrice = 0;
    products.forEach(product => {
        totalPrice += product.count * product.price;
    });
    return totalPrice;
}


function updateTotalPriceDisplay(reset=false) {
    const totalPriceSpan = document.getElementById('total-price'); 
    if (totalPriceSpan) {
        totalPriceSpan.textContent = `Total: ${calculateTotalPrice().toFixed(2)} €`;
    }
    if (reset) {
        totalPriceSpan.textContent = `Total: 0 €`;
    }
}