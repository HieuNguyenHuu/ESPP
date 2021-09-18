#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"
#include "freertos/FreeRTOSConfig.h"

#define configUSE_PREEMPTION 1
#define configUSE_TIME_SLICING 1

volatile uint32_t time_a = 0;
volatile uint32_t time_b = 0;


static const char* pcTextForTask1 = "Task 1 is running \r\n";
static const char* pcTextForTask2 = "Task 2 is running \r\n";

void vApplicationIdleHook(void)
{
    /* This hook function does nothing but increment a counter . */
    time_a++;
    time_b++;
}
void task_1(void* pvParameters) {
    const TickType_t xDelay100ms = pdMS_TO_TICKS(200);
    for (;; ) {
        printf("Task_1 with Delay Time: %d \n", time_a);
        vTaskDelay(xDelay100ms);
    }
    time_a = 0;
}
void task_2(void* pvParameters) {
    const TickType_t xDelay100ms = pdMS_TO_TICKS(100);
    for (;; ) {
        printf("Task_2 with Delay Time: %d \n", time_a);
        vTaskDelay(10 * xDelay100ms);
    }
    time_b = 0;
}

void app_main(void) {
    xTaskCreate(task_1, "Task 1", 4096, (void*)pcTextForTask1, 1, NULL);
    xTaskCreate(task_2, "Task 2", 4096, (void*)pcTextForTask2, 2, NULL);
    // vTaskStartScheduler();
}
void loop() {
    for (int i = 0; i < 2; i++) {
        vTaskSuspend(task_2)
        vTaskDelay(pdMS_TO_TICKS(4000));
        vTaskResume(task_2);
        vTaskDelay(pdMS_TO_TICKS(4000));
    }
}