#include <Servo.h>

Servo servo;

#include "EspMQTTClient.h"
EspMQTTClient client(
  "ABB_Gym_IOT",
  "Welcome2abb",
  "abb-mosca.cloud.abbspets.se",  // MQTT Broker server ip
  "vikramarduino",     // Client name that uniquely identifies your device
  1883              // The MQTT port, defaults to 1883. This line can be omitted
);

void setup() {
    servo.attach(5); // Assuming D1 is connected to pin 5
    servo.write(90); // Set the initial position to the center (90 degrees)
    delay(2000);
    client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
    client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridden with enableHTTPWebUpdater("user", "password").
    client.enableLastWillMessage("TestClient/lastwill", "I am going offline"); // You can activate the retain flag by setting the third parameter to true
}

void onConnectionEstablished() {
    // Subscribe to "vikram/forward-cm" and display received message to Serial
    client.subscribe("vikram/forward-cm", [](const String & payload) {
        Serial.println(payload);
        if (payload == "0") {
            servo.write(34);
        } else if (payload == "1") {
            servo.write(100); // Change the angle to 100 (you may adjust this value)
        }
    });
}

void loop() {
    client.loop();
    // Your additional loop code can go here if needed
}
