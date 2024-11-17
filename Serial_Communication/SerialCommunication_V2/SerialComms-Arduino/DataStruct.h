  // Arduino 1 Identification.
#ifndef AuthAR_H
#define AuthAR_H

struct AuthAR {
  String AuthData;
  String AuthID;
};

AuthAR aauth = {"Arduino", "41:72:64:75:69:6E:6F:2D:53:6C:61:76:65"}; // CONST

#endif

 // Data inputs...
#ifndef dataInputs_H
#define dataInputs_H

struct dataInputs {
  int Button_1; // Button 1 for test
  int Pot_1; // Potentiometer 1 for test
};

#endif