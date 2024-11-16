#ifndef sendMessage
#define sendMessage

void sendMessage() {
  String data = "ID:" + deviceID + ", AUTH:" + authToken + ", MSG:" + message;
  mySerial.println(data); // Send the data to ESP32
  Serial.println("Sent: " + data); // Print to Serial Monitor
}

#endif