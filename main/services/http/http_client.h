#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief 执行一次最小 HTTP GET 请求
     *
     * @param url 目标 URL
     */
    esp_err_t http_client_get(const char *url);

#ifdef __cplusplus
}
#endif
