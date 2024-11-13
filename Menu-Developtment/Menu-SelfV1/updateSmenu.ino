void updateSmenu() {
  if (SPointer == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Infos");
    infosSub();
  }

  if (SPointer == 3) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Electronics");
    ElectronicsSub();
  }
  /*
  if (SPointer == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Infos");
    infosSub();
  }

  if (SPointer == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Infos");
    infosSub();
  }

  if (SPointer == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Infos");
    infosSub();
  }
*/
}