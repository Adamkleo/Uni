# SI-practica-final

### Linux and macOS:
```bash
git clone https://github.com/yourusername/shopping-system.git
cd shopping-system
npm install
```

### Windows:
```bash
git clone https://github.com/yourusername/shopping-system.git
cd shopping-system
npm install
```

```bash
node src/server.js
```

Open your web browser and navigate to http://localhost:3000/ to choose between the Customer and Attendant interfaces or directly access:

Customer Interface: http://localhost:3000/customer
Attendant Interface: http://localhost:3000/attendant


**C. System Description:**

1. Web application where store attendants can view customer products.
2. Mobile web application as a ubiquitous interaction device to replace the traditional shopping cart.
3. Server to manage the system:
   - Web: for both web and mobile applications.
   - WebSocket: to manage the ubiquitous interaction device.

**D. Minimum Interaction Requirements:**


1. Managing products in the shopping cart: Alternatives like sensors (GPS, Bluetooth, NFC, etc.) or the webcam can be used.
   - Add: A product, for example, hanging on a rack, should be added to the system through a ubiquitous interaction.
   - Remove: A product already added to the system can be removed through a ubiquitous interaction.
   - Mark as Favorite: A product from the list can be marked as a favorite through a ubiquitous interaction.
   - Sort: Products in the list can be sorted ubiquitously through some ubiquitous interaction.
   - Notification or payment notice for the shopping cart to store attendants: This interaction will replace the traditional scanning of products at the checkout. Some ubiquitous interaction will be chosen to request payment (for example, using sensors to identify proximity, gestures, voice, etc.).
2. Identification of additional functionalities: In the design process, each group should identify 2 additional functionalities and provide ubiquitous interaction alternatives for each functionality.

**E. Prototype Implementation:**
It's important to consider that this project is a prototype, not a final product, meant to explore mobile interaction possibilities for list management. Therefore, aspects like application security, scalability, server performance, database usage, etc., won't be addressed. The prototype will be implemented to work with a single user per profile (one customer, one store attendant).
To implement the prototype, the technologies seen in class will be used:
1. Interaction from the mobile application will be implemented using Web APIs: Touch, Speech, Sensor, Vibration, etc.
2. The mobile and web applications will exchange interaction-related data using socket.io.

**DELIVER**
  - Implementation of the network architecture (servers) using Node.js, Express, and socket.io.
  - Implementation of web applications: one with the interface for the store attendant and the other for the store customer.
  - Implementation of interactions using WEB APIs: Touch, Speech, Sensor, etc.


**Evaluation:**
Each group's developed system will be presented and defended in class in week 14, on the date indicated in the schedule. The project grade accounts for 60% of the final grade for the course.
- Design 20%: 5% Analysis + 5% Creation + 10% Documentation
- Implementation 25%: 5% Servers + 5% Web Applications + 15% Interactions
- Evaluation 10%: 5% Protocol + 5% Results
- Defense 5%