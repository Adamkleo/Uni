var socket = io.connect(window.location.origin);

function acceptOrder() {
    let firstOrder = document.querySelector('.order-container'); 
    if (firstOrder) {
        const orderId = firstOrder.id;
        const orderDetails = []; 

        
        firstOrder.querySelectorAll('.product-name').forEach(item => {
            orderDetails.push(item.textContent);
        });

        socket.emit('confirmed', { orderId: orderId, orderDetails: orderDetails });
        console.log(`Order ${orderId} accepted`);
        firstOrder.remove(); 
    } else {
        console.log("No orders to accept.");
    }
}

function rejectOrder() {
    let firstOrder = document.querySelector('.order-container'); 
    if (firstOrder) {
        const orderId = firstOrder.id;
        console.log(`Order ${orderId} rejected`);
        firstOrder.remove(); 
    } else {
        console.log("No orders to reject.");
    }
}


document.addEventListener('DOMContentLoaded', function () {
    var orderCount = 0;  

    socket.on('newOrder', function (orderDetails) {
        orderCount++;  
        const orderId = `order-${orderCount}`;

        
        const orderContainer = document.createElement('div');
        orderContainer.className = 'order-container';
        orderContainer.id = orderId;

        
        const orderHeader = document.createElement('h2');
        orderHeader.textContent = `Order ID: ${orderId}`;
        orderContainer.appendChild(orderHeader);

        const productList = document.createElement('div');
        productList.className = 'order-list product-grid';  
        

        
        
        orderDetails.forEach(item => {
            const productContainer = document.createElement('div');
            productContainer.className = 'product-item';

            
            const productImage = document.createElement('img');
            productImage.className = 'product-image';
            let imageName = item.toLowerCase().replace(/%20/g, ' '); 
            imageName = imageName.replace(/\s+/g, '-'); 
            imageName = imageName.split('-')[0]; 
            const imageExtension = (imageName === 'manzanas') ? 'png' : 'jpg'; 
            productImage.src = `../assets/products/${imageName}.${imageExtension}`;
            productContainer.appendChild(productImage);


            const productName = document.createElement('span');
            productName.className = 'product-name';  
            productName.textContent = item;
            productContainer.appendChild(productName);


            productList.appendChild(productContainer);

        });
        
        orderContainer.appendChild(productList);
        
        const acceptButton = document.createElement('button');
        acceptButton.textContent = 'Accept';
        acceptButton.onclick = function () {
            socket.emit('confirmed', { orderId: orderId, orderDetails: orderDetails });
            console.log(`Order ${orderId} accepted`);
            document.getElementById(orderId).remove();

        };


        const rejectButton = document.createElement('button');
        rejectButton.textContent = 'Reject';
        rejectButton.onclick = function () {
            document.getElementById(orderId).remove();
            console.log(`Order ${orderId} rejected`);
        };

        orderContainer.appendChild(acceptButton);
        orderContainer.appendChild(rejectButton);

        document.getElementById('order-list').appendChild(orderContainer);
    });
});


function toggleView(view) {
    const views = document.querySelectorAll('.view');
    views.forEach(v => v.style.display = 'none');  
    const targetView = document.getElementById(view);
    if (targetView) {
        targetView.style.display = 'block'; 
    }
}

function submitProduct() {
    console.log("Submit Product Called"); 
    const name = document.getElementById('product-name').value;
    const price = parseFloat(document.getElementById('product-price').value);
    const imageFile = document.getElementById('product-image').files[0];

    console.log(name, price, imageFile); 

    if (!name || isNaN(price) || !imageFile) {
        alert('Please fill in all fields correctly.');
        return;
    }

    const reader = new FileReader();
    reader.onload = function(event) {
        const imgData = event.target.result;
        console.log(imgData); 
        socket.emit('newProduct', { name, price, image: imgData });
    };
    reader.readAsDataURL(imageFile);
}
