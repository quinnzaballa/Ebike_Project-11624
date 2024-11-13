#include <HardwareSerial.h>
#include "functions.h" 

// Define UART interface for communication
HardwareSerial mySerial(1);

// Unique ID and Auth Token for ESP32
String receiverID = "Arduino_001";
String expectedAuthToken = "AUTH1234";

void setup() {
  Serial.begin(9600);    // Serial monitor
  mySerial.begin(9600, SERIAL_8N1, 16, 17);  // UART1, RX:16, TX:17

  Serial.println("Initializing ESP32...");
}

void loop() {
  if (mySerial.available()) {
    String receivedData = mySerial.readStringUntil('\n'); // Read until newline

    Serial.println("Received: " + receivedData); // Show the full received data
    
    // Parse the message and check if the ID and Auth Token match
    if (validateMessage(receivedData, receiverID, expectedAuthToken)) {
      Serial.println("Message is valid!");
      // Further processing of the received message
    } else {
      Serial.println("Invalid message.");
    }
  }
}
