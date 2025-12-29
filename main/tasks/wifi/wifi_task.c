#include "wifi_task.h"

#include "wifi.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#define WIFI_TASK_STACK_SIZE 4096
#define WIFI_TASK_PRIORITY 5

static const char *TAG = "wifi_task";
static EventGroupHandle_t wifi_event_group = NULL;
static EventBits_t wifi_ready_bit = 0;

static void wifi_task(void *arg)
{
    (void)arg;

    ESP_LOGI(TAG, "[%s] wifi task start", pcTaskGetName(NULL));

    if (wifi_service_init() != ESP_OK)
    {
        ESP_LOGE(TAG, "wifi init failed");
        vTaskDelete(NULL);
        return;
    }

    while (1)
    {
        if (wifi_service_is_connected())
        {
            xEventGroupSetBits(wifi_event_group, wifi_ready_bit);
        }
        else
        {
            xEventGroupClearBits(wifi_event_group, wifi_ready_bit);
        }

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void wifi_task_start(EventGroupHandle_t event_group, EventBits_t ready_bit)
{
    wifi_event_group = event_group;
    wifi_ready_bit = ready_bit;
    xTaskCreate(wifi_task,
                "wifi_task",
                WIFI_TASK_STACK_SIZE,
                NULL,
                WIFI_TASK_PRIORITY,
                NULL);
}
