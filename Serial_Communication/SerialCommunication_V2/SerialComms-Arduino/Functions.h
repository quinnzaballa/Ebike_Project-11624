// Start of AuthARF function(s)
#ifndef AuthARF_H
#define AuthARF_H

  // Probably for debug only or send data to ESP32-Master

String AuthARF (void *ParamsStruct, String type) {
  AuthAR *aauthptr = (AuthAR *)ParamsStruct;

  //ALL DATA PRINT!
  if (type == "ALL") {
  Serial.print(aauthptr->AuthID);
  Serial.print(", ");
  Serial.println(aauthptr->AuthData);
  return;
  }

  // Return data (single instance)
  if (type == "AuthID") {
  Serial.println(aauthptr->AuthID);
  } else if (type == "AuthData") {
  Serial.println(aauthptr->AuthData);
  return;
  }


  Serial.println("Type isn't configured/unknown!");

}
#endif
// end of AuthARF function



// Start of the strtauth function(s) 
#ifndef strtauth_H
#define strtauth_H

/*
|| Defintions:
||  dataIN = String data from Serial.readStringUntil
||  wte = What to expect? ie; ESP32-Slave or Arduino
*/

int strtauth(String dataIN, String wte) {
  
  if (wte == "ESP32-Master") {
  dataIN.replace(" ", ""); // remove spaces in the text.
  
  Serial.println("RequestAllowed-ESP32_MASTER"); // Send Clearance text to ESP32-Master

  // Initialize timeout
  unsigned long timeout = millis() + 5000;

  while (true) {
    
    // Timeout
    if (millis() > timeout) {
    // Serial.println("Time out!"); was jsut for debug...
    return 2; // Return value 2 for timeout.
    }

    if (Serial.available() > 0) {
    String incS = Serial.readStringUntil('\n');

    // Check if the ESP32 was done authentication
    if (incS == "Okay!") {
      return 1;
      } else return 0;

   }
  }
 }
}

  /* Debug
  Serial.println(dataIN);
  */

#endif // end of strtauth


// Start initializeCommsA
#ifndef initializeCommsA_H
#define initializeCommsA_H

int initializeCommsA() {
  // Start reading for incoming bytes|String|data.
    while (true) {

    if (Serial.available() > 0) {
      String dataincstr = Serial.readStringUntil('\n'); // Process incoming data stream and turn to String
      int returncode = strtauth(dataincstr, "ESP32-Master");

      if (returncode == 1) {
      Serial.println("Connected and Sync successfully!");
      return 1; // Return 1 if connected else 0.
      } else if (returncode == 0) {
         Serial.println("Error code: 01");
      }

      if (returncode == 2) {
      Serial.println("Timeout reached! please restart the MCU of target!");
      }

   }
  }
}

#endif
// end of initializeCommsA