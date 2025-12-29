#pragma once

#include "esp_err.h"
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t sdcard_service_mount(const char *mount_point);
void sdcard_service_unmount(void);
bool sdcard_service_is_mounted(void);

#ifdef __cplusplus
}
#endif
