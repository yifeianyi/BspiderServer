#pragma once

#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"

#ifdef __cplusplus
extern "C" {
#endif

void wifi_task_start(EventGroupHandle_t event_group, EventBits_t ready_bit);

#ifdef __cplusplus
}
#endif
