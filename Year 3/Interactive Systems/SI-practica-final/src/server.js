const express = require('express');
const app = express();
const http = require('http').Server(app);
const io = require('socket.io')(http);
const fs = require('fs');
const path = require('path');  
const ordersPath = 'orders.json';  

app.use(express.static('public'));

io.on('connection', (socket) => {
    console.log('New client connected');

    socket.on('disconnect', () => console.log('Client disconnected'));

    socket.on('order', (orderDetails) => {
        console.log('Order received:', orderDetails);
        socket.broadcast.emit('newOrder', orderDetails);
    });

    socket.on('newProduct', (productDetails) => {
        console.log('New product received:', productDetails);
        
        socket.broadcast.emit('productAdded', productDetails);
    });

    socket.on('confirmed', (data) => {
        console.log('Order confirmed:', data.orderId);

        fs.readFile(ordersPath, (err, fileData) => {
            if (err) {
                console.error('Error reading from file:', err);
                return;  
            }

            let orders;
            try {
                orders = JSON.parse(fileData.toString());
                if (!Array.isArray(orders)) {  
                    console.error('Expected an array but got:', typeof orders);
                    orders = [];  
                }
            } catch (parseError) {
                console.error('Error parsing JSON from file:', parseError);
                orders = [];  
            }

            console.log('Current orders array:', orders);  

            orders.push(data);

            fs.writeFile(ordersPath, JSON.stringify(orders, null, 4), (err) => {
                if (err) {
                    console.error('Error writing to file:', err);
                } else {
                    console.log('Order saved:', data.orderId);
                }
            });
        });
    });
});

const PORT = 3000;
http.listen(PORT, () => console.log(`Server running on port ${PORT}`));
