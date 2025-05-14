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
    
    uint8_t x = 0;
    uint8_t lcd_id[12];
    esp_err_t ret;

    ret = nvs_flash_init();             /* 初始化 NVS */
    if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }

    led_init();                                                         /* 初始化LED */
    i2c0_master = iic_init(I2C_NUM_0);                                  /* 初始化IIC0 */
    xl9555_init(i2c0_master);                                           /* IO扩展芯片初始化 */
    ltdc_init();                                                        /* RGB屏初始化 */

    sprintf((char *)lcd_id, "LCD ID:%04X", ltdcdev.id);                 /* 将LCD ID打印到lcd_id数组 */

    while(1)
    {
        switch (x)
        {
            case 0:
                ltdc_clear(WHITE);
                break;

            case 1:
                ltdc_clear(BLACK);
                break;

            case 2:
                ltdc_clear(BLUE);
                break;

            case 3:
                ltdc_clear(RED);
                break;

            case 4:
                ltdc_clear(MAGENTA);
                break;

            case 5:
                ltdc_clear(GREEN);
                break;

            case 6:
                ltdc_clear(CYAN);
                break;

            case 7:
                ltdc_clear(YELLOW);
                break;
        }
        ltdc_show_string(10, 40, 240, 32, 32, "ESP32S3", RED);
        ltdc_show_string(10, 80, 240, 24, 24, "LTDC TEST", RED);
        ltdc_show_string(10, 110, 240, 16, 16, "ATOM@ALIENTEK", RED);
        ltdc_show_string(10, 130, 240, 16, 16, (char *)lcd_id, RED);    /* 显示LCD ID */

        x++;

        if (x == 8)
        {
            x = 0;
        }

        vTaskDelay(1000);
    }
}
