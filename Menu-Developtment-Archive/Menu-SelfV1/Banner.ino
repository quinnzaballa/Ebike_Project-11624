  // Main Menu Banner
void define_menu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Main Menu");
  updatemenu();
  loop();
}

  // Sub Menu Banner (Specific)