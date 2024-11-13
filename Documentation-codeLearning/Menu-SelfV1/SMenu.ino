void infosSub() {
  lcd.setCursor(0, 1);
  if (SubPointer == 0) lcd.print("Version           ");
  if (SubPointer == 1) lcd.print("Name              ");
  if (SubPointer == 2) lcd.print("Variant           ");
  if (SubPointer == 3) lcd.print("Serial            ");
}

void ElectronicsSub() {
  lcd.setCursor(0, 1);
  if (SubPointer == 0) lcd.print("Relay_TOG           ");
  if (SubPointer == 1) lcd.print("Ele2              ");
  if (SubPointer == 2) lcd.print("Ele3           ");
  if (SubPointer == 3) lcd.print("Ele4            ");
}