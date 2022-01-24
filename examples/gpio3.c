#include <driver/gpio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>

#define LED                GPIO_NUM_23
#define BUTTON             GPIO_NUM_27              /// Push Button

/**
 * @brief callback function for esp interruption
 * 
 * @param intr_mask 
 * @param high 
 * @param args optional args
 * @return gpio_intr_handler_fn_t 
 */
static void IRAM_ATTR intr_button(void* args)
{
    static bool led_state = false;
    led_state = led_state ? false : true;
    gpio_set_level(LED, led_state);                 
}

void app_main() {
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);      /// set LED as output
    
    gpio_set_direction(BUTTON, GPIO_MODE_INPUT);    /// set BUTTON as input
    gpio_pulldown_dis(BUTTON);                      /// disable pull-down resistor
    gpio_pullup_en(BUTTON);                         /// enable pull-up resistor
    
    /// allow esp to allocated intr
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);

    gpio_intr_enable(BUTTON);                       /// enable interruption
    gpio_set_intr_type(BUTTON, GPIO_INTR_NEGEDGE);  /// interrupt when BUTTON detect falling edge
    
    gpio_isr_handler_remove(BUTTON);                 /// remove intr handle
    /// add intr_button as intr handle
    gpio_isr_handler_add(
        BUTTON,             /// GPIO
        intr_button,        /// isr function
        NULL                /// args
    );              
    while(true)
    {
        /// keep esp running
    }
}