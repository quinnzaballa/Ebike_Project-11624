/*
|| Arduino Side
|| Send data and auth
*/
#include "DataStruct.h"
#include "Functions.h"


void setup() {
  Serial.begin(115200);
  // Nothing to do here. Maybe
}

void loop() {
  // Start reading for incoming bytes|String|data.
  while (true) {
  if (Serial.available() > 0) {
    String dataincstr = Serial.readStringUntil('\n'); // Process incoming data stream and turn to String
    // delay(500); // Debounce to make sure the data sent is complete..
    strtauth(dataincstr, "ESP32-Master");
   }
  }
}
