  /* 
  ||
  ||
  || Arduino class start here
  ||
  ||
  */


#include "structure.h"

#ifndef DatainputsC_H
#define DatainputsC_H


class DatainputsC {

  private:
  dataInputs dinput;
  dataInputs* dinputptr;

  public:
  // Contructor
  DatainputsC(int value_button1, int value_pot1) {
    dinput.Button_1 = value_button1;
    dinput.Pot_1 = value_pot1;
    dinputptr = &dinput;
  }

  void write(int value_button1, int value_pot1) {
    dinputptr->Button_1 = value_button1;
    dinputptr->Pot_1 = value_pot1;
  }

  dataInputs* getDataptr() {
    return dinputptr;
  }

};

#endif


  /* 
  ||
  ||
  || Arduino class end here
  ||
  ||
  */