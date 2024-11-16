#ifndef AuthARF_H
#define AuthARF_H

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


  Serial.println("Type is'nt configured/unknown!");

}


#endif