void setup() {
  Serial.begin(115200); // For debug only
  SArduino.begin(115200, SERIAL_8N1, 16, 17);
  SArduino.println("Authentication Initialization...");
  Serial.println("Authentication Initialization...");

  // Start authentication...

  byte clrAd = false;
  
  while (true) {

    String dataArecv = SArduino.readStringUntil('\n');
    // Trim to makesure theres no other immaculate random things
    dataArecv.trim();

    if (dataArecv == "RequestAllowed-ESP32_MASTER") {
      Serial.println("Data received and got Clearance!. Sending Okay!");
      SArduino.println("Okay!");
      clrAd = true;
    }

    if (clrAd && dataArecv == "Connected and Sync successfully!") {
      Serial.println("Done running loop.");
      break;
    }
  }
}