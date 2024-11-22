
// Ticks set to 1000Hz
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "driver/gpio.h"
#define light 2

//Blinking Task
void BlinkTask(void *pvParameters)
{
    esp_rom_gpio_pad_select_gpio(light);
    gpio_set_direction(light,GPIO_MODE_OUTPUT);

    int level = 0;
    for (;;)
    {
        level = !level;
        gpio_set_level(light,level);
        // Blink on for 1 sec and off for 0.3 sec
        if (level == 1){
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
        else{
            vTaskDelay(300 / portTICK_PERIOD_MS);
        }
    }
}

void app_main()
{
    TaskHandle_t xHandle1 = NULL;
    xTaskCreatePinnedToCore(BlinkTask,       // Entry function of the task
                            "Task1",      // Name of the task
                            10000,        // The number of words to allocate for use as the task's stack (arbitrary size enough for this task)
                            NULL,         // No parameter passed to the task
                            1,            // Priority of the task
                            &xHandle1,    // Handle to the created task
                            0);           // Task must be executed on core 0

    for (;;)
    {
        printf("Port Tick: %ld\n",portTICK_PERIOD_MS);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    };
}
