#include <driver/gpio.h>
#include <driver/adc.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_log.h>
#include <esp_event.h>

#define LED                GPIO_NUM_32
#define ADC2               ADC2_CHANNEL_8 /// gpio 25



int app_main()
{
    esp_err_t ret;
    float voltage = 0;
    int raw = 0;
    uint32_t res = 0x400;
    gpio_set_direction(LED, GPIO_MODE_OUTPUT);
    ret = adc2_config_channel_atten(ADC2, ADC_ATTEN_DB_11); // ~ 2650mv
    if(ret == ESP_OK)
        ESP_LOGI("MAIN", "ADC INICIALIZADO");
    while (true) {
        vTaskDelay(pdMS_TO_TICKS(1000));
        ret = adc2_get_raw(ADC2, ADC_WIDTH_BIT_10, &raw);
        
        voltage = raw  * 2.65 / res;
        ESP_LOGI("MAIN","Voltage: %f", voltage);
    }
    return 0;
}