  // Keypad Driver
#include <Key.h>
#include <Keypad.h>

const byte ROWS = 2;             /* */
const byte COLS = 2;              // Keypad Variable

  // Initialize keypad global bytes pin
byte rowPins[ROWS] = {2, 3};
byte colPins[COLS] = {A0, A1};

  // Define Keymap(s)
char keys[ROWS][COLS] = {
    {'1', 'A'},
    {'2', 'E'}
};

  // Create a keypad object 4x4
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


  // LCD Driver
#include <LiquidCrystal_I2C.h>


  // Initiate and make known global variable for LCD
LiquidCrystal_I2C lcd(0x27, 0, 2);

  // misc Scopes
  unsigned long Prevmili = 0;
  unsigned long currmili = millis();

  // Other Pin for interface
int Relaypin = 4;

  // Define and create Global Vars
int SMenu = 3;             /* */
int MMenu = 4;              //-- Max limit of menus
int SubPointer = 0;      // Subpointer if in the submenu
int SPointer = 0;        // Select pointer of Main menu
int Cursor = 0;         // Cursor to navigate
int SelectMenu = 0;     // This select the selected menu, Very specific
bool inSmenu = false;    // In sub menu?
bool isApressed = false; // independent global select button

void loop() {
  // Start char
  char key = keypad.getKey();
  //declaration of all choices for blinking or etc.
  

/*
  //Debug Temp A button, Should be a Select Buttonn
  if (key == 'A') {
    inSmenu = !inSmenu;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Tog_inSmenu:");
    lcd.setCursor(0, 1);
    lcd.print(inSmenu);
    delay(1000);
    define_menu();
  }
*/

  // Selector "E"
  // EXIT force/Main Menu
  if (key == 'E') {
    // Reset every Global
    SubPointer = 0;
    SPointer = 0;
    Cursor = 0;
    SelectMenu = 0;
    inSmenu = false;
    isApressed = false;
    lcd.clear();
    define_menu();
    loop();
  }


  // Selector "A"
  // Selector for Submenu
  if (key == 'A') {
    if (inSmenu == true) {
      SelectMenu = SPointer + SubPointer;
      SubPointer = 0;
      SelSub();
    }
  }


  if (key == 'A') {
    if (!inSmenu) { // Run if not in the menu yet or first execution.
    inSmenu = true;
    SPointer = Cursor + 1;
    Cursor = 0;
    updateSmenu();
    } else { // Continue if in the SubMenu.
    updateSmenu();
    }
  }

  // Start navigator
  if (key) {
    if (key == '2') {
        Cursor++;
        if (!inSmenu && Cursor > MMenu ) Cursor = 0;
        if (inSmenu && Cursor > SMenu) Cursor = 0;
    }
   
    if (key == '1') {
        Cursor--;
        if (!inSmenu && Cursor < 0) Cursor = MMenu;
        if (inSmenu && Cursor < 0) Cursor = SMenu;
    }
  
  if (inSmenu == true) {
    SubPointer = Cursor;
    updateSmenu();
  } else { updatemenu(); }

  // Callers
  updatemenu();


  // LCD Definer Debug Only
  /*
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Current Sel:");
  lcd.setCursor(0, 1);
  lcd.print(Cursor);
  */
  }

DebugONLY();
}

// END OF THE LOOP, Contains debug and etc.
void DebugONLY() {
  // Debug Only line
  Serial.print(" | Cursor: ");
  Serial.print(Cursor);
  Serial.print(" | Debug_InSmenu: ");
  Serial.print(inSmenu);
  Serial.print(" | SPointer: ");
  Serial.print(SPointer);
  Serial.print(" | SubPointer: ");
  Serial.print(SubPointer);
  Serial.print(" | Selectmenu: ");
  Serial.print(SelectMenu);
  Serial.print(" | Relaypin: ");
  Serial.print(digitalRead(Relaypin));

  // Debug arduino runtime
  Serial.print(" | Total Run: ");
  Serial.print(millis());
  Serial.print(" | Total Prev: ");
  Serial.println(Prevmili);
  
  // Temp Slow
  delay(50);
  }


void skipall() {
  loop();
}