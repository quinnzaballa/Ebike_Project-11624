void SelSub() {

  // Infos Submenu
  if (SPointer == 1) {
    // Version
    if (SelectMenu == 1) { 
      skipall();
    }


  }

  // Electronics Submenu
  if (SPointer == 3) {

    // Relay Toggle
    if (SelectMenu == 3) {
      char key = keypad.getKey();

        if (key == 'A') {
        SelectMenu = 0;
        Prevmili = 0;
        digitalWrite(Relaypin, LOW);
        loop();
        }

        relay_loop_toogle();
        

    }
  }
}
