/*
|| Arduino Side
|| Send data and auth
*/
#include "DataStruct.h"
#include "Functions.h"

byte iniA = false;


void loop() {
  // Call initializer 
  if (!iniA) { // Run for the first time if wasnt initialized. Itll run again when a code didnt get the pleasure. then reset iniA..
  int returncode = initializeCommsA();
    if (returncode == 1) {
      iniA = true;
    }
  }

  /*
  ||  Code starts here...
  ||  Use ArduinoSend() to each command for identifications..
  ||
  */



}