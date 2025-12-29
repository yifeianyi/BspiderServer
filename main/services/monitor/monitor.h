#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t monitor_task_start(void);
void monitor_task_entry(void *arg);

#ifdef __cplusplus
}
#endif
