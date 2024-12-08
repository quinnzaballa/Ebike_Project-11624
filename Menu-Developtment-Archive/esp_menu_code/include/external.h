/**
 * =====================================================
 * -------             external.h                -------
 * =====================================================
 * 
 *  This header is for linking and reduce clutterring
 * in the cpp's source.
 * 
 *  This header is important and hardlinked! so adju-
 * sting   and   modifying  this  header  would cause
 * problems.
 * 
 *  I ADVICE NOT TO TOUCH THIS FILE UNLESS YOU
 * KNOW WHAT YOURE DOING.
 * 
 *  (extern) means that it was declared here but it
 * was initialized somewhere else.  not here.  also
 * this  stops  the  cpp  sources to declare 2 same
 * thing   which   would   cause  compiling  issues
 * and wont clutter the main cpp because extern was
 * used in that cpp source(s).
 * 
 * idk what im saying :) - Quinn.
 */

//  ### Include custom libraries ###
#include "LiquidCrystal_I2C.h"
#include "Keypad.h"

/**
 * ==============================================
 * |||||||||||||||||||||||||||||||||||||||||||||||
 * ||                                           ||
 * ||        #Prototypes and Variables#         ||
 * ||   Always on top to stop compiler having   ||
 * ||   compiling Issues.                       ||
 * ||                                           ||
 * |||||||||||||||||||||||||||||||||||||||||||||||
 * ==============================================
 */

extern const char* menu_list[];                         // Menu lists where the lcd will get and print.
extern const int menu_list_size;                        // Menu list size.
extern void menu_get_size(const char** menu_list, bool debug_en);      // Get size of the menu_list
extern LiquidCrystal_I2C lcd;                           // this is defined somewhere else
extern Keypad kpd;                                      // this is defined somewhere else
extern void kpd_update();
extern void t_kpd_update(void *params);
extern void lcd_update();
extern void t_lcd_update(void *params);

/**
 * ==============================================
 * |||||||||||||||||||||||||||||||||||||||||||||||
 * ||                                           ||
 * ||               #Structures#                ||
 * ||                                           ||
 * |||||||||||||||||||||||||||||||||||||||||||||||
 * ==============================================
 */

// Structure for kpd to know what or where im pointing at.
// This also is important where i choosed or what.
struct kpd_variable {
    int selected_sub;       // add the pointer to 1 to identify when A was pressed.
    int pointer;            // where the kpd is.
    bool insubmenu;         // Tells if im IN the submenu or nahh..
    bool reset;             // Global reset. kpd_key E
};

extern kpd_variable _kpd_variable; // define values outside.

// Structure for analyzing the menu_list where the main/sub_menu is positioned.
struct menu_list_pos {
    int main_list_pos[5];      // It holds the position in 0 - inf value (Main Menu)
    int sub_list_pos[5];       // It holds the position in 0 - inf value (Sub Menu)
    int main_pos_count;                     // Maximum found (Main Menu)
    int sub_pos_count;                      // Maximum found (Sub Menu)
};

extern menu_list_pos _menu_list_pos; // Define values outside

struct menu_variables {
    bool led_toggle;
    int value;
    // menu_list system info max sub_menu.
    int sys_max_sub_menu;
};

extern menu_variables _menu_variables;

// Structure to combine the struct to pass to params (freertos task)
struct task_pass_params {
    kpd_variable __kpd_variable;
    menu_list_pos __menu_list_pos;
    menu_variables __menu_variables;
};

extern task_pass_params _task_pass_params; // Define values outside for compiler to know it was declared outside.