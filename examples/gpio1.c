#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED GPIO_NUM_23

#define LED_PRIORITY 1
#define LED_CORE_ID  0
TaskHandle_t switchLED_task_handle = NULL;

void switchLED_task (void *parameter)
{
    for(;;)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        static bool led_state = false;
        led_state = led_state == false ? true : false;
        gpio_set_level(LED, led_state);
        
    }
}

void app_main() {
    xTaskCreate(switchLED_task, "LED_task", 1000, NULL, LED_PRIORITY, &switchLED_task_handle);
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    
    while(true) {}
}