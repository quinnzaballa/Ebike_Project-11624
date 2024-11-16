/*
|| Arduino Side
|| Send data and auth
*/
#include "DataStruct.h"
#include "Functions.h"


void setup() {
  Serial.begin(115200);
  // Ignore boot info on ESP32's


  // Check for serial
  while (true) {
  int incSerial = Serial.read();
  Serial.println("ESP32: Boot info..");


  if (incSerial > -1) {
    // Initialize and Authenticate
    AuthARF(&aauth, "ALL");
   return;
   }
  }
}

void loop() {
    // Nothing to do here: YET
}
