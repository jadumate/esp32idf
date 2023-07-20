#include <stdio.h>
#include <string.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include "nvs_flash.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_gap_ble_api.h"

void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param)
{
    switch (event) {
        case ESP_GAP_BLE_SCAN_RESULT_EVT:
            if (param->scan_rst.search_evt == ESP_GAP_SEARCH_INQ_RES_EVT) {
                esp_bd_addr_t bd_addr;
                memcpy(bd_addr, param->scan_rst.bda, sizeof(esp_bd_addr_t));

                printf("Device found\n  ADDR : %02x:%02x:%02x:%02x:%02x:%02x\n",
                       bd_addr[0], bd_addr[1], bd_addr[2], bd_addr[3], bd_addr[4], bd_addr[5]);
                
                uint8_t len;
				uint8_t *data = esp_ble_resolve_adv_data(param->scan_rst.ble_adv, ESP_BLE_AD_TYPE_NAME_CMPL, &len);

                if(len >= 1) printf("  NAME : %.*s\n", len, data);
                else         printf("  NAME : (noname)\n");

                printf("  RSSI : %d\n", param->scan_rst.rssi);
                printf("\n");
            }
            break;

        default:
            break;
    }
}

void app_main()
{
    nvs_flash_init();    

    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_bt_controller_init(&bt_cfg);
    esp_bt_controller_enable(ESP_BT_MODE_BLE);

    esp_bluedroid_init();
    esp_bluedroid_enable();

    esp_ble_gap_register_callback(esp_gap_cb);
    esp_ble_gap_start_scanning(0);

    while (1) {
        vTaskDelay(1000 / portTICK_PERIOD_MS);  
    }
}