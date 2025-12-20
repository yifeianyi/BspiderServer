idf_component_register(
    SRCS
        "app_main.c"
        "services/wifi/wifi.c"

    INCLUDE_DIRS
        "services/wifi"
        "common"

    REQUIRES
        esp_wifi
        esp_event
        esp_netif
        nvs_flash

    PRIV_REQUIRES
        spi_flash
)
