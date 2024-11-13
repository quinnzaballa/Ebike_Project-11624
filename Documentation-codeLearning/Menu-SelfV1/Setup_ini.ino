void setup() {
  // Begin Serial: BAUD 9600
  Serial.begin(9600);
  Serial.print("Note: Serial is on!");
  // Input Dig/ADC pin here
  pinMode(Relaypin, OUTPUT);

  // Electronic test & Initiation
  // Relay(s) test
  // Electronic(Relay_TOG, )
  digitalWrite(Relaypin, HIGH);
  delay(150);
  digitalWrite(Relaypin, LOW);

  // LCD begin welcome
  delay(1000);
  lcd.begin();
  lcd.backlight();
  // Clear values
  Cursor = 0;
  lcd.clear();
  // Provide Welcome + Version
  lcd.print(" Prototype Menu");
  delay(790);
  lcd.setCursor(0, 1);
  lcd.print("   Debug Ver.2");
  delay(2000);
  define_menu();
}