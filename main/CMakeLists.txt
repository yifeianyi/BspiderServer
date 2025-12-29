idf_component_register(
    SRCS
        "app_main.c"
        "app/app_runtime.cpp"
        "tasks/wifi/wifi_task.c"
        "tasks/http/http_task.c"
        "tasks/monitor/monitor_task.c"
        "services/monitor/monitor.c"
        "services/wifi/wifi.c"
        "services/http/http_client.c"
        "services/sdcard/sdcard.c"

    INCLUDE_DIRS
        "app"
        "tasks/wifi"
        "tasks/http"
        "tasks/monitor"
        "services/wifi"
        "services/http"
        "services/monitor"
        "services/sdcard"
        "hal"

    REQUIRES
        esp_wifi
        esp_event
        esp_netif
        nvs_flash
        esp_http_client
        driver
        fatfs
        sdmmc

    PRIV_REQUIRES
        spi_flash
)
