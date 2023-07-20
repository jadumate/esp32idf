# esp32 - esp - idf
Examples for ESP-IDF on ESP32

+ blink.c : Simplest 1 port I/O blinker example
+ led.cpp : Simple class for on/off example using built-in LED and I/O pins

```
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
```


