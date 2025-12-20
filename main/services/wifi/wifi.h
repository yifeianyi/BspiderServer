#ifndef __WIFI_H__
#define __WIFI_H__

#include <stdbool.h>
#include "esp_err.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 初始化并启动 Wi-Fi STA
     */
    esp_err_t wifi_service_init(void);

    /**
     * @brief 当前是否已获取 IP（网络可用）
     */
    bool wifi_service_is_connected(void);

#ifdef __cplusplus
}
#endif

#endif
