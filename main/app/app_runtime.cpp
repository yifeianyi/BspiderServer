#include "app_runtime.h"

#include "wifi_task.h"
#include "http_task.h"
#include "monitor_task.h"
#include "sdcard.h"
#include "board.h"

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

static const char *TAG = "app_runtime";
static const EventBits_t kWifiReadyBit = BIT0;

// static EventGroupHandle_t app_event_group;

extern "C" void app_runtime_start(void)
{
    ESP_LOGI(TAG, "system start");

    // app_event_group = xEventGroupCreate();
    // if (!app_event_group)
    // {
    //     ESP_LOGE(TAG, "event group create failed");
    //     return;
    // }

    if (sdcard_service_mount(SD_MOUNT_POINT) != ESP_OK)
    {
        ESP_LOGW(TAG, "sdcard mount failed");
    }

    // wifi_task_start(app_event_group, kWifiReadyBit);
    // http_task_start(app_event_group, kWifiReadyBit);
    monitor_task_start_wrapper();
}
