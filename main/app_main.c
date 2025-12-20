#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "wifi.h"
#include "http_client.h"

static const char *TAG = "app_main";

void app_main(void)
{
    ESP_LOGI(TAG, "system start");

    wifi_service_init();

    /* 等待 Wi-Fi 就绪 */
    while (!wifi_service_is_connected())
    {
        ESP_LOGI(TAG, "waiting for network...");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    ESP_LOGI(TAG, "network ready, start http");

    /* 最小 HTTP 测试 */
    http_client_get("http://httpbin.org/get");

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
