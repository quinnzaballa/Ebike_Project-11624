#ifndef validateMessage_H
#define validateMessage_H

bool validateMessage(String data, String Recvdata, String expcAtoken) {
  // Extract ID and Auth Token from the received data
  String idPrefix = "ID:";
  String authPrefix = "AUTH:";

  int idStart = data.indexOf(idPrefix);
  int authStart = data.indexOf(authPrefix);
  
  if (idStart == -1 || authStart == -1) {
    return false; // Invalid message structure
  }

  // Extract the ID and Auth token by finding the commas
  int idEnd = data.indexOf(",", idStart);
  int authEnd = data.indexOf(",", authStart);

  String receivedID = data.substring(idStart + 3, idEnd);
  String receivedAuthToken = data.substring(authStart + 5, authEnd);
  
  Serial.print("Received ID: ");
  Serial.println(receivedID);
  Serial.print("Received Auth Token: ");
  Serial.println(receivedAuthToken);
  
  // Compare with the ESP32's receiver ID and expected Auth Token
  if (receivedID == Recvdata && receivedAuthToken == expcAtoken) {
    return true;
  } else {
    return false; // Invalid ID or Auth Token
  }
}

#endif // Validation