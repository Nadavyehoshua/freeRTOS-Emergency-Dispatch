#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "init.h"

// Define your stack size
#define TASK_STACK_SIZE  configMINIMAL_STACK_SIZE

// Example Task 1
void Task1(void *pvParameters) {
    while(1) {
        printf("[Task1] Running...\n");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(1000));  // Delay 1 second
    }
}

// Example Task 2
void Task2(void *pvParameters) {
    while(1) {
        printf("[Task2] Running...\n");
        fflush(stdout);
        vTaskDelay(pdMS_TO_TICKS(2000));  // Delay 2 seconds
    }
}

int main(void) {
    // Initialize FreeRTOS
    init_main();

    printf("\n=== FreeRTOS Project Starting ===\n\n");
    fflush(stdout);

    // Create your tasks here
    xTaskCreate(Task1, "Task1", TASK_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task2, "Task2", TASK_STACK_SIZE, NULL, 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    printf("Scheduler failed to start!\n");
    while(1);

    return 0;
}
