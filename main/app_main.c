#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "wifi.h"

static const char *TAG = "app_main";

void app_main(void)
{
    ESP_LOGI(TAG, "system start");

    wifi_service_init();

    while (1)
    {
        if (wifi_service_is_connected())
        {
            ESP_LOGI(TAG, "network ready");
        }
        else
        {
            ESP_LOGI(TAG, "waiting for network...");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}
