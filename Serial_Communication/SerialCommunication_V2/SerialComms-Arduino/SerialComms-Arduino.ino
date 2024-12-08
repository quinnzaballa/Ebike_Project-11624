#include <class.h>
#include <functions.h>
#include <structure.h>

/*
|| Arduino Side
|| Send data and auth
*/

// Const data in test input
// Potentiometer 1
const int pot1 = A0;

DatainputsC dataIN(0, 0);

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
  
  /* Map pot value (debug only) */
  int potm = analogRead(pot1);
  int potval = map(potm, 0, 1023, 0, 255);
  dataIN.write(0, potval);

  dataInputs* dinputptr = dataIN.getDataptr();
  Serial.print("Pointer value1: ");
  Serial.println(dinputptr->Pot_1);
}