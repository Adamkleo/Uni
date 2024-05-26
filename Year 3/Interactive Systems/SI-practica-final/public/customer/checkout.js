document.addEventListener('DOMContentLoaded', function() {
    const socket = io.connect(window.location.origin);

    window.finalizePurchase = function() {
        
        const checkoutItems = document.getElementById('checkout-items');
        const items = Array.from(checkoutItems.children).map(item => item.textContent.trim());
        if (items.length === 0) {
            alert('Your cart is empty. Please add items to your cart before finalizing your purchase.');
            return; 
        }
        
        socket.emit('order', items);

        
        alert('Purchase completed!');

        
        if (window.products) {
            window.products.forEach(product => product.count = 0);
        }
        
        
        const cartItems = document.getElementById('cart-items');
        if (cartItems) {
            cartItems.querySelectorAll('.product-item').forEach(item => {
                item.querySelector('span').textContent = '0';
            });
        }
        updateTotalPriceDisplay(true);  

        
        toggleView('shop');
    };
});


