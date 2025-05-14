#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "nvs_flash.h"
#include "esp_system.h"
#include "esp_chip_info.h"
#include "esp_psram.h"
#include "esp_flash.h"

#include "led.h"
#include "ltdc.h"

// 初始化IIC协议
i2c_obj_t i2c0_master;

void app_main(void)
{
    esp_err_t ret;
    uint32_t flash_size;
    esp_chip_info_t chip_info;          /* 定义芯片信息结构体变量 */
    ret = nvs_flash_init();             /* 初始化 NVS */

    if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    esp_flash_get_size(NULL, &flash_size);              /* 获取 FLASH 大小 */
    esp_chip_info(&chip_info);
    /* 获取 CPU 内核数并显示 */
    printf("内核：cpu数量%d\n",chip_info.cores);                
    /* 获取 FLASH 大小并显示 */
    printf("FLASH size:%ld MB flash\n",flash_size / (1024 * 1024));
    /* 获取 PARAM 大小并显示 */
    printf("PARAM size: %d bytes\n", esp_psram_get_size());

    while(1)
    {
        printf("Hello ESP32\r\n");
        vTaskDelay(1000);
    }

}
