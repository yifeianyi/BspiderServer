idf_component_register(
    SRCS
        "app_main.c"
        "services/wifi/wifi.c"
        "services/http/http_client.c"

    INCLUDE_DIRS
        "services/wifi"
        "services/http"
        "common"

    REQUIRES
        esp_wifi
        esp_event
        esp_netif
        nvs_flash
        esp_http_client

    PRIV_REQUIRES
        spi_flash
)
