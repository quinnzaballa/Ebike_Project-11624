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
#endif // end of AuthARF function


#ifndef strtauth_H
#define strtauth_H

/*
||  wte = What to expect? ie; ESP32-Slave or Arduino
*/

int strtauth(String dataIN, String wte) {
  if (wte == "ESP32-Master") {
  
  dataIN.replace(" ", ""); // remove spaces in the text.
  
  /* Debug
  Serial.println(dataIN);
  */

  /*
  || Start indexing and data processing
  */
  
  Serial.println("RequestAllowed-ESP32_MASTER");

  }
}

#endif // end of strtauth..

