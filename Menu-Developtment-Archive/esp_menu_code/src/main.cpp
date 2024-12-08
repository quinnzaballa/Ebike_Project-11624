/**
 * ==============================================
 * ||||||||||||||||||||||||||||||||||||||||||||||
 * ||                                          ||
 * ||             INCLUDE SECTION              ||
 * ||                                          ||
 * ||||||||||||||||||||||||||||||||||||||||||||||
 * ==============================================
 */

// include FreeRTOS headers that would be used 
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

// Include gpio driver
#include <driver/gpio.h>

// Custom Libraries/Headers
#include "external.h"
#include "LiquidCrystal_I2C.h"
#include "Keypad.h"

/**
 * ==============================================
 * |||||||||||||||||||||||||||||||||||||||||||||||
 * ||                                           ||
 * ||           #APP_MAIN / SETUP()#            ||
 * ||                                           ||
 * |||||||||||||||||||||||||||||||||||||||||||||||
 * ==============================================
 */

extern "C" void app_main()
{
    lcd.init();
    lcd.backlight();

    menu_get_size(menu_list, true);

    // ## tasks creation here. Loop..

    xTaskCreate(
        t_kpd_update,
        "keypad task",
        10000,
        NULL,
        0,
        NULL
    );

    xTaskCreate(
        t_lcd_update,
        "LCD task",
        10000,
        NULL,
        0,
        NULL
    );
}