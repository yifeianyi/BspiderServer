#include "monitor.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_heap_caps.h"
#include "esp_system.h"

#define MONITOR_TASK_STACK_SIZE 4096
#define MONITOR_TASK_PRIORITY 5
#define MONITOR_INTERVAL_MS 5000

static const char *TAG = "monitor_task";
static TaskHandle_t monitor_task_handle = NULL;

void monitor_task_entry(void *arg)
{
    (void)arg;

    while (1)
    {
        size_t free_heap = esp_get_free_heap_size();
        size_t min_free_heap = esp_get_minimum_free_heap_size();
        size_t free_8bit = heap_caps_get_free_size(MALLOC_CAP_8BIT);
        size_t free_32bit = heap_caps_get_free_size(MALLOC_CAP_32BIT);

        ESP_LOGI(TAG, "heap free=%u, min_free=%u, 8bit=%u, 32bit=%u",
                 (unsigned)free_heap,
                 (unsigned)min_free_heap,
                 (unsigned)free_8bit,
                 (unsigned)free_32bit);

#if CONFIG_FREERTOS_USE_TRACE_FACILITY
        {
            char *task_list = (char *)pvPortMalloc(1024);
            if (task_list)
            {
                ESP_LOGI(TAG, "[%s] task list:\nName          State Prio Stack Num\n",
                         pcTaskGetName(NULL));
                vTaskList(task_list);
                ESP_LOGI(TAG, "[%s]\n%s", pcTaskGetName(NULL), task_list);
                vPortFree(task_list);
            }
            else
            {
                ESP_LOGW(TAG, "[%s] task list skipped: no memory", pcTaskGetName(NULL));
            }
        }
#endif

#if CONFIG_FREERTOS_GENERATE_RUN_TIME_STATS
        {
            char *run_stats = (char *)pvPortMalloc(1024);
            if (run_stats)
            {
                ESP_LOGI(TAG, "[%s] run time stats:\nTask          Time  CPU(%)\n",
                         pcTaskGetName(NULL));
                vTaskGetRunTimeStats(run_stats);
                ESP_LOGI(TAG, "[%s]\n%s", pcTaskGetName(NULL), run_stats);
                vPortFree(run_stats);
            }
            else
            {
                ESP_LOGW(TAG, "[%s] run time stats skipped: no memory", pcTaskGetName(NULL));
            }
        }
#endif

        vTaskDelay(pdMS_TO_TICKS(MONITOR_INTERVAL_MS));
    }
}

esp_err_t monitor_task_start(void)
{
    if (monitor_task_handle)
    {
        return ESP_ERR_INVALID_STATE;
    }

    BaseType_t ok = xTaskCreate(monitor_task_entry,
                                "monitor_task",
                                MONITOR_TASK_STACK_SIZE,
                                NULL,
                                MONITOR_TASK_PRIORITY,
                                &monitor_task_handle);

    return (ok == pdPASS) ? ESP_OK : ESP_FAIL;
}
