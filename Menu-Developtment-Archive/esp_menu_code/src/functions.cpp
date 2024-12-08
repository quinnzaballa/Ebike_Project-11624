/**
 * ==============================================
 * -------         Functions.cpp          -------
 * ==============================================
 * 
 *  This section defines and holds functions that
 * is    declared   in   the   external.h   file. 
 * 
 *  Modifying this cpp would likely cause proble-
 * ms, so  if you know what you are doing you can
 * modify this file. IF not then dont.
 * 
 *  IT IS RECOMMEDED TO NOT TOUCH WITHOUT LEARNI-
 * NG THE CODEBASE FIRST!
 */

//  ### Include custom libraries ###
#include "external.h"
#include "LiquidCrystal_I2C.h"
#include "Keypad.h"

/**
 * ==============================================
 * ||||||||||||||||||||||||||||||||||||||||||||||
 * ||                                          ||
 * ||      THE SUFFERING STARTS HERE :D        ||
 * ||                                          ||
 * ||||||||||||||||||||||||||||||||||||||||||||||
 * ==============================================
 */

// LCD implementation.
LiquidCrystal_I2C lcd(0x27, 16, 2);

/**
 * #####################
 *   Keypad makeKeymap
 * #####################
 */

const byte ROWS = 2, COLS = 2;
byte row_pin[ROWS] = {19, 18}, col_pin[COLS] = {5, 17};
char kpd_layout[ROWS][COLS] =
{
    {'1', 'A'},
    {'2', 'E'}
};
Keypad kpd = Keypad(makeKeymap(kpd_layout), row_pin, col_pin, ROWS, COLS);

/**
 * #####################
 *       menu_list
 * #####################
 */

const char* menu_list[] =
{
        // Start of LED menu
    "1_LED",            // Main menu Identifier
    "LED",              // Print to LCD <- Reprint for sub_menu.
        // Sub_menu
    "2_LED",             // Sub menu Identifier
    "LED %s",           // Print to LCD
   
        // Start of System info menu
    "1_System Info",    // Main menu Identifier
    "System Info",      // Print to LCD <- Reprint for sub_menu.
        // Sub_menu
    "2_System Info",    // Sub menu Identifier
    "ESP32 cpu id",     // Print to lcd
    "Version",          // Print to lcd
    
        // Value; if up. increment, if down. decrement.
    "1_Value",          // Main menu Identifier
    "Value",            // Print to LCD <- Reprint for sub_menu.
        // Sub_menu     
    "2_Value",          // Sub menu Identifier
    "Value %d"          // Print to LCD
   //1234567890123456   Just for max char 16 columns.
};



// Get the maximum size of the menu_list / IM LAZY EVEN ITS SMOL IDGF
constexpr int menu_list_size = sizeof(menu_list)/sizeof(char*);

/**
 * ==============================================
 * ||||||||||||||||||||||||||||||||||||||||||||||||
 * ||                                            ||
 * ||                 Structures                 ||
 * ||  Implementation/initialization of structs  ||
 * ||                                            ||
 * ||||||||||||||||||||||||||||||||||||||||||||||||
 * ==============================================
 */

kpd_variable _kpd_variable =
{
    .selected_sub = 0,
    .pointer = 0,
    .insubmenu = false,
    .reset = false
};

menu_list_pos _menu_list_pos =
{
    .main_list_pos = {0},
    .sub_list_pos = {0},
    .main_pos_count = 0,
    .sub_pos_count = 0
};

menu_variables _menu_variables =
{
    .led_toggle = false,
    .value = 0,
    .sys_max_sub_menu = 2
};

task_pass_params _task_pass_params = // This feels getting deprecated
{
    .__kpd_variable = _kpd_variable,
    .__menu_list_pos = _menu_list_pos,
    .__menu_variables = _menu_variables
};

/**
 * ==============================================
 * ||||||||||||||||||||||||||||||||||||||||||||||
 * ||                                          ||
 * ||      FUNCTIONS IMPLEMENTATION HERE       ||
 * ||                                          ||
 * ||||||||||||||||||||||||||||||||||||||||||||||
 * ==============================================
 */

// ###### get menu size ######
void menu_get_size(const char** menu_list, bool debug_en)
{
    /**
     *  This function serves purpose of saving the position
     * as  it  sweeps thru out the menu_list. Should be ran
     * at the app_main() at the very top.
     */

    for (int i = 0; i < menu_list_size; i++)
    {
        if (menu_list[i][0] == '1')
        {
            _menu_list_pos.main_list_pos[_menu_list_pos.main_pos_count] = i;
            _menu_list_pos.main_pos_count++;
        } else if (menu_list[i][0] == '2')
        {
            _menu_list_pos.sub_list_pos[_menu_list_pos.sub_pos_count] = i;
            _menu_list_pos.sub_pos_count++;
        }
    }

    if (debug_en)
    {
        for (int i = 0; i < _menu_list_pos.main_pos_count; i++)
        {
            printf("INDEX: %d, CONTENT: %s\n", _menu_list_pos.main_list_pos[i], menu_list[_menu_list_pos.main_list_pos[i]]);
        }

        for (int i = 0; i < _menu_list_pos.sub_pos_count; i++)
        {
            printf("INDEX: %d, CONTENT: %s\n", _menu_list_pos.sub_list_pos[i], menu_list[_menu_list_pos.sub_list_pos[i]]);
        }
    }
}

// ###### keypad Update. ######
void kpd_update()
{
    //task_pass_params *getparams = (task_pass_params *)pvparams; useless
    /**
     *  This function serves a important role
     * as this function read and send data to
     * the  kpd_variable which the lcd_update
     * will read and update the lcd.
     */

    //  Get keypad input. Should be looped at most 1-24ms for
    // the key pressed.
    char kpd_getKey = kpd.getKey(); 

    // ## This section reads the kpd_getKey ##
    if (kpd_getKey != NO_KEY) // If keypad get key is not. then run this executions below
    {
        if (kpd_getKey == '1') // Check if UP was pressed.
        {
            _kpd_variable.pointer++;
            if (!_kpd_variable.insubmenu && _kpd_variable.pointer > _menu_list_pos.main_pos_count - 1) _kpd_variable.pointer = 0;
            if (_kpd_variable.insubmenu && _kpd_variable.pointer > _menu_list_pos.sub_pos_count - 1) _kpd_variable.pointer = 0;
        } else if (kpd_getKey == '2')
        {
            _kpd_variable.pointer--;
            if (!_kpd_variable.insubmenu && _kpd_variable.pointer < 0) _kpd_variable.pointer = _menu_list_pos.main_pos_count - 1;
            if (_kpd_variable.insubmenu && _kpd_variable.pointer < 0) _kpd_variable.pointer = _menu_list_pos.sub_pos_count - 1;
        } else if (kpd_getKey == 'A')
        {
            
            if (!_kpd_variable.insubmenu) {_kpd_variable.selected_sub = _kpd_variable.pointer + 1;} else {} 
        }
    }
}

// ###### LCD Update. ######
void lcd_update()
{
    // get copy of kpd variable to compare and check if there were an update.
    kpd_variable _cpkpd_variable =
    {
        .selected_sub = 1, // Just 1st run, itll get replaced after.
        .pointer = 0,
        .insubmenu = false,
        .reset = false
    };

    bool printonlyonce = false; // this prints Main Menu on start only once, let row 2 be updated

    // Only run once to stop lcd getting these bs obvious refresh.
    if ( _cpkpd_variable.insubmenu       !=      _kpd_variable.insubmenu
                                         ||
         _cpkpd_variable.pointer         !=      _kpd_variable.pointer
                                         ||
         _cpkpd_variable.reset           !=      _kpd_variable.reset
                                         ||
         _cpkpd_variable.selected_sub    !=      _kpd_variable.selected_sub
       )
    {
        _cpkpd_variable = _kpd_variable; // Sync cp.

        if (!printonlyonce)
        {
            lcd.setCursor(0, 0);
            lcd.print("Main Menu");
        }

        if (!_kpd_variable.insubmenu)
        {
            lcd.setCursor(0, 1);
            lcd.printf("%s              ", menu_list[_menu_list_pos.main_list_pos[_kpd_variable.pointer] + 1]);
        }
    }
       
}

// ###### Keypad Update task ######
void t_kpd_update(void *params)
{
    while (1)
    {
    // This handles the kpd
    kpd_update();
    vTaskDelay(pdMS_TO_TICKS(24));
    // printf("POINTER: %d\n", _kpd_variable.pointer);
    }
}

// ###### Keypad Update task ######
void t_lcd_update(void *params)
{
    while (1)
    {
    // This handles the lcd.
    lcd_update();
    vTaskDelay(pdMS_TO_TICKS(100));
    }
}
