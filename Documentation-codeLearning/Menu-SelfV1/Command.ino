void relay_loop_toogle() {

  if (currmili - Prevmili >= 500) {
    Prevmili = currmili;
    byte Toggle = digitalRead(Relaypin);
    digitalWrite(Relaypin, Toggle);
    SelSub();
  }
}