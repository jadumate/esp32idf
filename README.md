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

+ blescan.c : Scanner for BLE, display ADDRESS, NAME, RSSI

You need to enable Bluetooth functionality in the sdkconfig file. (or use idf.py with 'menuconfig' on the prompt)
```
CONFIG_BT_ENABLED=y
CONFIG_BT_BLUEDROID_ENABLED=y
CONFIG_BT_CONTROLLER_ENABLED=y
```



