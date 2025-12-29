#include "sdcard.h"

#include "board.h"
#include "driver/spi_common.h"
#include "driver/spi_master.h"
#include "esp_log.h"
#include "esp_vfs_fat.h"
#include "sdmmc_cmd.h"
#include <stdio.h>

static const char *TAG = "sdcard_service";

static sdmmc_host_t host = SDSPI_HOST_DEFAULT();
static sdmmc_card_t *card = NULL;
static bool bus_initialized = false;
static bool mounted = false;
static const char *mounted_path = NULL;

static esp_err_t sdcard_init_bus(void)
{
    if (bus_initialized)
    {
        return ESP_OK;
    }

    host.slot = SD_SPI_HOST;

    spi_bus_config_t bus_cfg = {
        .mosi_io_num = SD_SPI_MOSI_GPIO,
        .miso_io_num = SD_SPI_MISO_GPIO,
        .sclk_io_num = SD_SPI_SCLK_GPIO,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 4000,
    };

    esp_err_t ret = spi_bus_initialize(host.slot, &bus_cfg, SPI_DMA_CH_AUTO);
    if (ret != ESP_OK && ret != ESP_ERR_INVALID_STATE)
    {
        return ret;
    }

    bus_initialized = true;
    return ESP_OK;
}

esp_err_t sdcard_service_mount(const char *mount_point)
{
    if (mounted)
    {
        return ESP_OK;
    }

    if (!mount_point)
    {
        return ESP_ERR_INVALID_ARG;
    }

    esp_err_t ret = sdcard_init_bus();
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "spi bus init failed: %s", esp_err_to_name(ret));
        return ret;
    }

    sdspi_device_config_t slot_config = SDSPI_DEVICE_CONFIG_DEFAULT();
    slot_config.gpio_cs = SD_SPI_CS_GPIO;
    slot_config.host_id = host.slot;

    esp_vfs_fat_sdmmc_mount_config_t mount_config = {
        .format_if_mount_failed = false,
        .max_files = 5,
        .allocation_unit_size = 16 * 1024,
    };

    ret = esp_vfs_fat_sdspi_mount(mount_point, &host, &slot_config, &mount_config, &card);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "sdcard mount failed: %s", esp_err_to_name(ret));
        return ret;
    }

    mounted = true;
    mounted_path = mount_point;

    sdmmc_card_print_info(stdout, card);
    ESP_LOGI(TAG, "sdcard mounted at %s", mount_point);
    return ESP_OK;
}

void sdcard_service_unmount(void)
{
    if (!mounted)
    {
        return;
    }

    esp_vfs_fat_sdcard_unmount(mounted_path, card);
    card = NULL;
    mounted = false;
    mounted_path = NULL;

    if (bus_initialized)
    {
        spi_bus_free(host.slot);
        bus_initialized = false;
    }

    ESP_LOGI(TAG, "sdcard unmounted");
}

bool sdcard_service_is_mounted(void)
{
    return mounted;
}
