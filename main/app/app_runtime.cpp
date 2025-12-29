#include "app_runtime.h"

#include "wifi.h"
#include "http_client.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

static const char *TAG = "app_runtime";
static const char *kDefaultUrl = "http://httpbin.org/get";

extern "C" void app_runtime_start(void)
{
    ESP_LOGI(TAG, "system start");

    if (wifi_service_init() != ESP_OK)
    {
        ESP_LOGE(TAG, "wifi init failed");
        return;
    }

    while (!wifi_service_is_connected())
    {
        ESP_LOGI(TAG, "waiting for network...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ESP_LOGI(TAG, "network ready, start http");

    http_client_get(kDefaultUrl);

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
