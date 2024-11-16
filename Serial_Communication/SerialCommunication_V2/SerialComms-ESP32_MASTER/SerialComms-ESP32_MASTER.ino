void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, 16, 17); // Serial for Arduino.
  Serial2.print("Authentication Request");

  // Set a timeout duration (in milliseconds) for waiting
  unsigned long timeout = millis() + 5000; // 5 seconds timeout

  while (true) {
    // Check if data is available
    if (Serial2.available() > 0) {
      String Authreqwait = Serial2.readStringUntil('\n');
      Authreqwait.trim();
      // Check if we received the expected response
      if (Authreqwait == "RequestAllowed-ESP32_MASTER") {
        Serial.println("Request Successful...");
        return; // Exit setup() and proceed
      } else {
        Serial.println("hmm.. Data got wasn't the expected authreq clearance.");
        Serial.println(Authreqwait);
      }
    }

    // Check for timeout
    if (millis() > timeout) {
      Serial.println("Timeout reached. No valid response received.");
      break; // Exit the loop if no response within timeout
    }
  }
}

void loop() {
  // Main code here, to run repeatedly
  Serial2.println("testtesttesttest");

   delay(1000);
}
