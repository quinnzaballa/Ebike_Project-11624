#include <SoftwareSerial.h>

// Define the pin numbers for UART communication
#define RX_PIN 10
#define TX_PIN 11

extern SoftwareSerial mySerial(RX_PIN, TX_PIN); // RX, TX pins

// Unique ID and Auth Token
String deviceID = "Arduino_001";
String authToken = "AUTH1234";

// Data to send
String message = "Hello from Arduino!";

void setup() {
  Serial.begin(9600);   // Serial monitor
  mySerial.begin(9600); // UART communication with ESP32
  
  Serial.println("Initializing Arduino...");

  // Send ID and Authentication token
  sendMessage();
}

void loop() {
  // Send data periodically
  delay(5000);  // Send every 5 seconds
  sendMessage();
}