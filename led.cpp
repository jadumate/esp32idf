#include <stdio.h>
#include <unistd.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define INTERNAL_LED_PIN GPIO_NUM_2  

extern "C" void app_main();

class TLed
{
protected :
    gpio_num_t m_pin;    

    void init()
    {
        esp_rom_gpio_pad_select_gpio(m_pin);
        gpio_set_direction(m_pin, GPIO_MODE_OUTPUT);
    };

public :     
    TLed (gpio_num_t pin) : m_pin(pin) { init(); };
    TLed(void) : m_pin(INTERNAL_LED_PIN) { init(); };

    void on(){ 
        gpio_set_level(m_pin, 1);
        vTaskDelay(10 / portTICK_PERIOD_MS);  
    }

    void off(){ 
        gpio_set_level(m_pin, 0);
        vTaskDelay(10 / portTICK_PERIOD_MS);  
    }
};

void app_main()
{
    TLed led;

    while(true){
        led.on();
        vTaskDelay(1000 / portTICK_PERIOD_MS);  
        led.off();
        vTaskDelay(1000 / portTICK_PERIOD_MS);  
    }
}
