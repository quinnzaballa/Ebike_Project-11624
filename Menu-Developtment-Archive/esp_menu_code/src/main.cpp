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

// include ESP system related
#include "esp_system.h"

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

    setup_gpio();

    // ## tasks creation here. Loop..

    if ( xTaskCreate(
        t_kpd_update,
        "keypad task",
        10000,
        NULL,
        0,
        NULL
    ) != pdPASS)
    {
        printf("TASK DIDNT RUN OR A PROBLEM!\n");
    } else {printf("Task kpd_update ran perfectly...\n");}

    if ( xTaskCreate(
        t_lcd_update,
        "LCD task",
        10000,
        NULL,
        0,
        NULL
    ) != pdPASS)
    {
        printf("TASK DIDNT RUN OR A PROBLEM!\n");
    } else {printf("Task lcd_update ran perfectly...\n");}

    if ( xTaskCreate (
        test,
        "test only",
        6000,
        &_task_pass_params,
        0,
        NULL
    ) != pdPASS)
    {
        printf("TASK DIDNT RUN OR A PROBLEM!\n");
    } else {printf("Task test_update ran perfectly...\n");}




    // vTaskStartScheduler(); <- DONT run, was my mistake. as the esp dev stated on the comments or note.
    /**
     * NOTE : In ESP-IDF the scheduler is started automatically during
     * application startup, vTaskStartScheduler() should not be called from
     * ESP-IDF applications.
     */
}