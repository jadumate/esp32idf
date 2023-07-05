#include <stdio.h>
#include <unistd.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define LED_GPIO 23 // LED port

void blinkLED(void *param) 
{
    gpio_reset_pin(LED_GPIO);
    gpio_set_direction(LED_GPIO, GPIO_MODE_OUTPUT);

    while(1) {        
        gpio_set_level(LED_GPIO, 0);  // LED OFF
        vTaskDelay(1000 / portTICK_PERIOD_MS);  // 1000ms = 1sec
        gpio_set_level(LED_GPIO, 1);  // LED ON
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    vTaskDelete(NULL);  // finishing the task
}

void app_main(void) {
    xTaskCreate(blinkLED, "task_led", 1024*2, NULL, 3, NULL);
}

