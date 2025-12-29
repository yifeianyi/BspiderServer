#include "monitor_task.h"

#include "monitor.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define MONITOR_TASK_STACK_SIZE 4096
#define MONITOR_TASK_PRIORITY 3

static void monitor_task(void *arg)
{
    monitor_task_entry(arg);
}

void monitor_task_start_wrapper(void)
{
    xTaskCreate(monitor_task,
                "monitor_task",
                MONITOR_TASK_STACK_SIZE,
                NULL,
                MONITOR_TASK_PRIORITY,
                NULL);
}
