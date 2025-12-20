#include "http_client.h"

#include "esp_http_client.h"
#include "esp_log.h"

static const char *TAG = "http_client";

/* HTTP 事件回调（最小实现） */
static esp_err_t http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id)
    {
    case HTTP_EVENT_ON_HEADER:
        ESP_LOGD(TAG, "header: %s = %s",
                 evt->header_key, evt->header_value);
        break;

    case HTTP_EVENT_ON_DATA:
        ESP_LOGI(TAG, "recv data len=%d", evt->data_len);
        break;

    case HTTP_EVENT_ON_FINISH:
        ESP_LOGI(TAG, "http finish");
        break;

    default:
        break;
    }
    return ESP_OK;
}

esp_err_t http_client_get(const char *url)
{
    ESP_LOGI(TAG, "http get: %s", url);

    esp_http_client_config_t config = {
        .url = url,
        .method = HTTP_METHOD_GET,
        .event_handler = http_event_handler,
        .timeout_ms = 5000,
    };

    esp_http_client_handle_t client =
        esp_http_client_init(&config);

    if (client == NULL)
    {
        ESP_LOGE(TAG, "http client init failed");
        return ESP_FAIL;
    }

    esp_err_t err = esp_http_client_perform(client);

    if (err == ESP_OK)
    {
        int status = esp_http_client_get_status_code(client);
        int length = esp_http_client_get_content_length(client);

        ESP_LOGI(TAG, "HTTP status = %d, content_length = %d",
                 status, length);
    }
    else
    {
        ESP_LOGE(TAG, "http request failed: %s",
                 esp_err_to_name(err));
    }

    esp_http_client_cleanup(client);
    return err;
}
