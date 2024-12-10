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
 * 
 *  Small note from me. Almost everything was le-
 * arned from chatgpt and online resources. small
 * story is i started with batch file then assem-
 * bly  then this. Its been long since ive coded.
 * 
 *  The  good  thing i can read some code because
 * how  its abit similar to batch coding. it took
 * me  1-3  weeks to learn the core basics of cpp
 * coding.  At  first i didnt really wanna switch
 * to  vscode  till i discovered platformio. made
 * things  easier and i can run both framework at
 * the  same time. Glad that all things ive lear-
 * ned really pulled off.
 * 
 *  Im   proudly   a  stem  student  currently in 
 * SPIST : CARBAG.  Funny thing this isnt my main
 * target.  its  my side hobby. The course i want 
 * is  to  become  a Aircraft Mechanic Technician
 * like  my  father.  I started with engines then 
 * this  because i was interested when i saw ASM.
 * 
 *  Thats all Thank you for reading if you did!
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
    "LED              ",              // Print to LCD <- Reprint for sub_menu.
        // Sub_menu
    "2_LED",             // Sub menu Identifier
    "LED: %s          ",           // Print to LCD
   
        // Start of System info menu
    "1_System Info",    // Main menu Identifier
    "System Info      ",      // Print to LCD <- Reprint for sub_menu.
        // Sub_menu
    "2_System Info",    // Sub menu Identifier
    "cpuid            ",     // Print to lcd
    "Ver              ",          // Print to lcd
    
        // Value; if up. increment, if down. decrement.
    "1_Value",          // Main menu Identifier
    "Value            ",            // Print to LCD <- Reprint for sub_menu.
        // Sub_menu     
    "2_Value",          // Sub menu Identifier
    "Value %d         "          // Print to LCD
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

reset_verify _reset_verify =
{
    .done_pass_1 = 0,
    .done_pass_2 = 0,
    .done_pass_3 = 0,
    .done_pass_4 = 0
};

task_pass_params _task_pass_params = 
{
    .__kpd_variable = &_kpd_variable,
    .__menu_list_pos = &_menu_list_pos,
    .__menu_variables = &_menu_variables,
    .__reset_verify = &_reset_verify
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

    for (int i = 0; i < menu_list_size; i++) // Loop until menu list size
    {
        if (menu_list[i][0] == '1') // This checks if identifier 1 is there
        {
            _menu_list_pos.main_list_pos[_menu_list_pos.main_pos_count] = i; // save the position.
            _menu_list_pos.main_pos_count++; // Increments the count for next position array.
        } else if (menu_list[i][0] == '2') // same as here.
        {
            _menu_list_pos.sub_list_pos[_menu_list_pos.sub_pos_count] = i; // same here
            _menu_list_pos.sub_pos_count++; // same here
        }
    }

    if (debug_en) // for debug
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
     *  This function serves an important role
     * as  this function read and send data to
     * the  kpd_variable  which the lcd_update
     * will read and update the lcd. this sec-
     * tion  is  partialy  abit  unreadable :>
     * 
     */

    //  Get keypad input. Should be looped at most 1-24ms for
    // the key pressed.
    char kpd_getKey = kpd.getKey(); 

    // ## This section reads the kpd_getKey ##
    if (kpd_getKey != NO_KEY) // If keypad get key is not. then run this executions below
    {
        if (kpd_getKey == '1') // Check if UP was pressed.
        {
            if (_kpd_variable.selected_sub == 3)
            {
                _menu_variables.value++;
                run_code_sub_menu();
                return;
            }

            // Continue if not value yet
            _kpd_variable.pointer++;
            if (!_kpd_variable.insubmenu && _kpd_variable.pointer > _menu_list_pos.main_pos_count - 1) _kpd_variable.pointer = 0;   // Main Menu
            if (_kpd_variable.insubmenu && _kpd_variable.pointer > _menu_variables.sys_max_sub_menu && _kpd_variable.selected_sub == 2) 
            {
                _kpd_variable.pointer = 1;
            } else if (_kpd_variable.insubmenu && _kpd_variable.pointer > _menu_list_pos.sub_pos_count - 1) _kpd_variable.pointer = 0;     // Sub Menu
            if (_kpd_variable.selected_sub == 2) run_code_sub_menu(); // system info
            
        } else if (kpd_getKey == '2') // Check if Down was pressed.
        {
            if (_kpd_variable.selected_sub == 3)
            {
                _menu_variables.value--;
                run_code_sub_menu();
                return;
            }

            // Continue if not value yet
            _kpd_variable.pointer--;
            if (!_kpd_variable.insubmenu && _kpd_variable.pointer < 0) _kpd_variable.pointer = _menu_list_pos.main_pos_count - 1;   // Main Menu
            if (_kpd_variable.insubmenu && _kpd_variable.pointer < 0) _kpd_variable.pointer = _menu_list_pos.sub_pos_count - 1;     // Sub Menu
            if (_kpd_variable.insubmenu && _kpd_variable.pointer < 1 && _kpd_variable.selected_sub == 2) _kpd_variable.pointer = _menu_variables.sys_max_sub_menu;
            if (_kpd_variable.selected_sub == 2) run_code_sub_menu(); // system info

        } else if (kpd_getKey == 'A') // Check if Select was pressed.
        {
            if (!_kpd_variable.insubmenu) {_kpd_variable.selected_sub = _kpd_variable.pointer + 1; _kpd_variable.insubmenu = true; run_code_sub_menu();} else
            {
                if (_kpd_variable.insubmenu && _kpd_variable.selected_sub == 1) _menu_variables.led_toggle = !_menu_variables.led_toggle; // if in the LED section, prob toggle this then continue.
                run_code_sub_menu(); // Run code IF in submenu
            }

        } else if (kpd_getKey == 'E') // check if exit/reset was pressed.
        {
            // Reset everything
            _kpd_variable = {0, 0, false, true};
            _menu_variables = {false, 0, 2};
            // ## runcode sub reset ##
            prevload = menu_list_size;
            printed = false;
            val_prevval = 0;
            runonlyonce2 = false;
            sys_sel = 0;
            // Pass after reset.
            _reset_verify.done_pass_2 = 1;
        }
    }
}

// ###### LCD Update. ######
bool printonlyonce = false; // this prints Main Menu on start only once, let row 2 be updated
bool runonlyonce2 = false;

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

    if (_kpd_variable.reset) 
    {
        printonlyonce = false;
        _reset_verify.done_pass_1 = 1;
        _cpkpd_variable.selected_sub = 5; // keeps reset if theres a difference.
        return;
    }

    // Only run once to stop lcd getting these bs obvious refresh.
    if ( _cpkpd_variable.insubmenu       !=      _kpd_variable.insubmenu
                                         ||
         _cpkpd_variable.pointer         !=      _kpd_variable.pointer
                                         ||
         _cpkpd_variable.selected_sub    !=      _kpd_variable.selected_sub
       )
    {
        _cpkpd_variable = _kpd_variable; // Sync cp.

        if (!printonlyonce && _kpd_variable.selected_sub == 0)
        {
            lcd.setCursor(0, 0);
            lcd.print("Main Menu        ");
            printonlyonce = true;
        }

        if (!_kpd_variable.insubmenu)
        {
            lcd.setCursor(0, 1);
            lcd.printf("%s", menu_list[_menu_list_pos.main_list_pos[_kpd_variable.pointer] + 1]);
        } else if (_kpd_variable.insubmenu && !runonlyonce2) // if in submenu, just update runcode submenu / new update : just once.
        {
            runonlyonce2 = true;
            run_code_sub_menu();
        }

        return;

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
    vTaskDelay(pdMS_TO_TICKS(48));
    }
}


// ###### test only lol ######
void test(void *params)
{
    while (1)
    {
        // ## Reset here. ##
        if (_kpd_variable.reset) // checks and reset.
        {
            if (_reset_verify.done_pass_1 == 1 && _reset_verify.done_pass_2 == 1)
            {
                _kpd_variable.reset = false;
                printf("Done resetting, current value: %d\n", _kpd_variable.reset);
            }
        }// else printf("Reset is not pressed yet.\n");
        
        vTaskDelay(pdMS_TO_TICKS(200));
    }

}


// TODO print the sub menu.
// [x] LED
// [ ] System Info
// [x] Value
// ###### Run code on the selected sub. ######
int prevload = 0;
bool printed = false;
bool led_prevvalue = 1; // LED
int val_prevval = 0;    // Value
bool val_bool_fr = false;// Value
int sys_sel = 0;

void run_code_sub_menu()
{
    if (prevload != _kpd_variable.selected_sub)  // Only run once after selecting a sub menu.
    {
        if (_kpd_variable.selected_sub == 2) // for System info specifically.
        {
            prevload = _kpd_variable.selected_sub;
            lcd.setCursor(0, 0);
            lcd.print("Sys info:");
            //         1234567890123456
        } else // This is for other sub menus.
        {
            prevload = _kpd_variable.selected_sub;
            lcd.setCursor(0, 0);
            lcd.printf(menu_list[_menu_list_pos.main_list_pos[_kpd_variable.selected_sub - 1] + 1]);
        }
    }

    if (_kpd_variable.selected_sub == 1) // LED
    {
        if (led_prevvalue != _menu_variables.led_toggle)
        {
            led_prevvalue = _menu_variables.led_toggle;
            gpio_set_level(GPIO_NUM_16, _menu_variables.led_toggle);
            lcd.setCursor(0, 1);
            lcd.printf(menu_list[_menu_list_pos.sub_list_pos[0] + 1], _menu_variables.led_toggle ? "ON" : "OFF");
        }

    } else if (_kpd_variable.selected_sub == 3) // VALUE
    {
        if (val_prevval != _menu_variables.value || !val_bool_fr) // val_bool_fr is responsible for single run
        {
            val_prevval = _menu_variables.value;
            val_bool_fr = false;
            lcd.setCursor(0, 1);
            lcd.printf(menu_list[_menu_list_pos.sub_list_pos[2] + 1], _menu_variables.value);
        }
    } else if (_kpd_variable.selected_sub == 2) // System Info
    {
        if (sys_sel != _kpd_variable.pointer && _kpd_variable.pointer == 1)
        {
            lcd.setCursor(10, 0);
            lcd.print("cpuid        ");
            lcd.setCursor(0, 1);
            lcd.print("idk.         ");
        } else 
        {
            lcd.setCursor(10, 0);
            lcd.print("ver          ");
            lcd.setCursor(0, 1);
            lcd.print(CURR_VERSION);
        }

    }

}

// as the name of function. its obvious.
void setup_gpio()
{
    gpio_config_t led_tog;
    led_tog.intr_type   = GPIO_INTR_DISABLE;
    led_tog.mode        = GPIO_MODE_OUTPUT;
    led_tog.pin_bit_mask= (1ULL<<GPIO_NUM_16); // Ill use 1ULL, idk but it doesnt really matter ig? chatgpt suggested it.
    led_tog.pull_down_en= GPIO_PULLDOWN_DISABLE;
    led_tog.pull_up_en  = GPIO_PULLUP_DISABLE;
    gpio_config(&led_tog);
}