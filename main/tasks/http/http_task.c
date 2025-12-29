#include "http_task.h"

#include "http_client.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"

#define HTTP_TASK_STACK_SIZE 4096
#define HTTP_TASK_PRIORITY 4

static const char *TAG = "http_task";
static const char *kDefaultUrl = "http://httpbin.org/get";
static EventGroupHandle_t http_event_group = NULL;
static EventBits_t http_ready_bit = 0;

static void http_task(void *arg)
{
    (void)arg;

    ESP_LOGI(TAG, "[%s] http task start", pcTaskGetName(NULL));

    while (1)
    {
        xEventGroupWaitBits(http_event_group,
                            http_ready_bit,
                            pdFALSE,
                            pdTRUE,
                            portMAX_DELAY);

        ESP_LOGI(TAG, "[%s] http get start", pcTaskGetName(NULL));
        http_client_get(kDefaultUrl);

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void http_task_start(EventGroupHandle_t event_group, EventBits_t ready_bit)
{
    http_event_group = event_group;
    http_ready_bit = ready_bit;
    xTaskCreate(http_task,
                "http_task",
                HTTP_TASK_STACK_SIZE,
                NULL,
                HTTP_TASK_PRIORITY,
                NULL);
}
