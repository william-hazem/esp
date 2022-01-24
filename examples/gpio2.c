#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

#define LED                GPIO_NUM_23
#define BUTTON             GPIO_NUM_27

void app_main() {
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);      /// set LED as output
    
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);    /// set BUTTON as input
    gpio_pulldown_dis(BUTTON);                      /// disable pull-down resistor
    gpio_pullup_en(BUTTON);                         /// enable pull-up resistor
    
    while(true)
    {
        vTaskDelay(10 / portTICK_PERIOD_MS);        /// 10ms delay
        int level = gpio_get_level(BUTTON);         /// get BUTTON state level
        gpio_set_level(LED, level);                 /// set LED ouput as BUTTON read value
    }
    
}