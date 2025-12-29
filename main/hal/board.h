#pragma once
#include "driver/gpio.h"
#include "driver/spi_common.h"

#define LED_GPIO GPIO_NUM_2

#define SD_SPI_HOST SPI2_HOST
#define SD_SPI_MOSI_GPIO GPIO_NUM_23
#define SD_SPI_MISO_GPIO GPIO_NUM_19
#define SD_SPI_SCLK_GPIO GPIO_NUM_18
#define SD_SPI_CS_GPIO GPIO_NUM_5

#define SD_MOUNT_POINT "/sdcard"
