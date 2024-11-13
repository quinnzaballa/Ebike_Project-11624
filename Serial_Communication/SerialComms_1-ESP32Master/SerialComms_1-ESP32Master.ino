#include <HardwareSerial.h>

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
    if (validateMessage(receivedData)) {
      Serial.println("Message is valid!");
      // Further processing of the received message
    } else {
      Serial.println("Invalid message.");
    }
  }
}

bool validateMessage(String data) {
  // Extract ID and Auth Token from the received data
  String idPrefix = "ID:";
  String authPrefix = "AUTH:";

  int idStart = data.indexOf(idPrefix);
  int authStart = data.indexOf(authPrefix);
  
  if (idStart == -1 || authStart == -1) {
    return false; // Invalid message structure
  }

  // Extract the ID and Auth token by finding the commas
  int idEnd = data.indexOf(",", idStart);
  int authEnd = data.indexOf(",", authStart);

  String receivedID = data.substring(idStart + 3, idEnd);
  String receivedAuthToken = data.substring(authStart + 5, authEnd);
  
  Serial.print("Received ID: ");
  Serial.println(receivedID);
  Serial.print("Received Auth Token: ");
  Serial.println(receivedAuthToken);
  
  // Compare with the ESP32's receiver ID and expected Auth Token
  if (receivedID == receiverID && receivedAuthToken == expectedAuthToken) {
    return true;
  } else {
    return false; // Invalid ID or Auth Token
  }
}
