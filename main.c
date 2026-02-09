#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "init.h"
#include "emergency_dispatch.h"
#include "semphr.h"

// Define your stack size
#define TASK_STACK_SIZE  configMINIMAL_STACK_SIZE

//resouces 
int Police[NUM_POLICE];
int Ambulance[NUM_AMBULANCE];
int Fire[NUM_FIRE];
int Covid[NUM_COVID];
int counter = 0;
//handlers
TaskHandle_t Event_generator_handler = NULL;
TaskHandle_t Logger_handler = NULL;
TaskHandle_t Dispatcher_handler = NULL;
TaskHandle_t Covid1_handler = NULL;
TaskHandle_t Covid2_handler = NULL;
TaskHandle_t Covid3_handler = NULL;
TaskHandle_t Covid4_handler = NULL;
TaskHandle_t Fire1_handler = NULL;
TaskHandle_t Fire2_handler = NULL;
TaskHandle_t Fire3_handler = NULL;
TaskHandle_t Police1_handler = NULL;
TaskHandle_t Police2_handler = NULL;
TaskHandle_t Police3_handler = NULL;
TaskHandle_t Ambulance1_handler = NULL;
TaskHandle_t Ambulance2_handler = NULL;
TaskHandle_t Ambulance3_handler = NULL;
TaskHandle_t Ambulance4_handler = NULL;

QueueHandle_t xDispatcherQueue = NULL;
QueueHandle_t xPoliceQueue = NULL;
QueueHandle_t xFireQueue = NULL;
QueueHandle_t xAmbulanceQueue = NULL;
QueueHandle_t xCovidQueue = NULL;
QueueHandle_t xLoggerQueue = NULL;

SemaphoreHandle_t xPoliceSemaphore;
SemaphoreHandle_t xAmbulanceSemaphore;
SemaphoreHandle_t xFireSemaphore;
SemaphoreHandle_t xCovidSemaphore;
//tasks
void Police1_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xPoliceQueue,&event,portMAX_DELAY);
        xSemaphoreTake(xPoliceSemaphore,portMAX_DELAY);
        xQueueSend(xLoggerQueue,&event,portMAX_DELAY);
        vTaskDelay(1000 + rand() % 2000);
        xSemaphoreGive(xPoliceSemaphore);
    }
}
void Police2_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xPoliceQueue,&event,portMAX_DELAY);

    }
}
void Police3_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xPoliceQueue,&event,portMAX_DELAY);

    }
}
void Ambulance1_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xAmbulanceQueue,&event,portMAX_DELAY);

    }
}
void Ambulance2_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xAmbulanceQueue,&event,portMAX_DELAY);

    }
}
void Ambulance3_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xAmbulanceQueue,&event,portMAX_DELAY);

    }
}

void Ambulance4_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xAmbulanceQueue,&event,portMAX_DELAY);

    }
}

void Fire1_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xFireQueue,&event,portMAX_DELAY);

    }
}
void Fire2_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xFireQueue,&event,portMAX_DELAY);

    }
}
 void Fire3_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xFireQueue,&event,portMAX_DELAY);

    }
}
void Covid1_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xCovidQueue,&event,portMAX_DELAY);

    }
}
void Covid2_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xCovidQueue,&event,portMAX_DELAY);

    }
}
void Covid3_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xCovidQueue,&event,portMAX_DELAY);

    }
}
void Covid4_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xCovidQueue,&event,portMAX_DELAY);

    }
}
void Dispatcher_task(void *pvParameters){
            Event_t event;

    while (1)
    {
        xQueueReceive(xDispatcherQueue,&event,portMAX_DELAY);
        printf("Event_id = %d\n",event.event_id);
        switch(event.event_type){
            case EVENT_POLICE:
                xQueueSend(xPoliceQueue,&event,portMAX_DELAY);
            break;
            case EVENT_AMBULANCE:
                xQueueSend(xAmbulanceQueue,&event,portMAX_DELAY);
            break;
            case EVENT_FIRE:
                xQueueSend(xFireQueue,&event,portMAX_DELAY);
            break;
            case EVENT_COVID:
                 xQueueSend(xCovidQueue,&event,portMAX_DELAY);
            break;
            default:
            break;
    }
    }
    
    
}
void Logger_task(void *pvParameters){


}
void Event_generator_task(void *pvParameters){
Event_t event;
while(1){
    event.event_id = counter++;
    event.event_type = (rand() % 4 + 1);

    xQueueSend(xDispatcherQueue,&event,portMAX_DELAY);

    vTaskDelay(pdMS_TO_TICKS(1000 + rand() % 4000));
}
}


int main(void) {
    // Initialize FreeRTOS
    init_main();

    // Create Queues
    xDispatcherQueue = xQueueCreate(DISPATCHER_QUEUE_LENGTH, sizeof(Event_t));
    xPoliceQueue = xQueueCreate(POLICE_QUEUE_LENGTH, sizeof(Event_t));
    xAmbulanceQueue = xQueueCreate(AMBULANCE_QUEUE_LENGTH, sizeof(Event_t));
    xFireQueue = xQueueCreate(FIRE_QUEUE_LENGTH, sizeof(Event_t));
    xCovidQueue = xQueueCreate(COVID_QUEUE_LENGTH, sizeof(Event_t));
    xLoggerQueue = xQueueCreate(LOGGER_QUEUE_LENGTH, sizeof(Event_t));

    // Check if queues were created successfully
    if (xDispatcherQueue == NULL || xPoliceQueue == NULL ||
        xAmbulanceQueue == NULL || xFireQueue == NULL ||
        xCovidQueue == NULL || xLoggerQueue == NULL) {
        printf("ERROR: Failed to create queues!\n");
        while(1); // Halt execution
    }

    // Create Semaphores
    xPoliceSemaphore = xSemaphoreCreateCounting(NUM_POLICE, NUM_POLICE);
    xAmbulanceSemaphore = xSemaphoreCreateCounting(NUM_AMBULANCE, NUM_AMBULANCE);
    xFireSemaphore = xSemaphoreCreateCounting(NUM_FIRE, NUM_FIRE);
    xCovidSemaphore = xSemaphoreCreateCounting(NUM_COVID, NUM_COVID);

    // Check if semaphores were created successfully
    if (xPoliceSemaphore == NULL || xAmbulanceSemaphore == NULL ||
        xFireSemaphore == NULL || xCovidSemaphore == NULL) {
        printf("ERROR: Failed to create semaphores!\n");
        while(1); // Halt execution
    }

    // Create Tasks
    BaseType_t taskStatus;

    // Create Dispatcher Task
    taskStatus = xTaskCreate(Dispatcher_task, "Dispatcher", TASK_STACK_SIZE, NULL, 4, &Dispatcher_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Dispatcher task!\n");
        while(1);
    }

    // Create Event Generator Task
    taskStatus = xTaskCreate(Event_generator_task, "Event_generator", TASK_STACK_SIZE, NULL, 1, &Event_generator_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Event Generator task!\n");
        while(1);
    }

    // Create Logger Task
    taskStatus = xTaskCreate(Logger_task, "Logger", TASK_STACK_SIZE, NULL, 0, &Logger_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Logger task!\n");
        while(1);
    }

    // Create Police Tasks
    taskStatus = xTaskCreate(Police1_task, "Police-1", TASK_STACK_SIZE, NULL, 3, &Police1_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Police1 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Police2_task, "Police-2", TASK_STACK_SIZE, NULL, 3, &Police2_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Police2 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Police3_task, "Police-3", TASK_STACK_SIZE, NULL, 3, &Police3_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Police3 task!\n");
        while(1);
    }

    // Create Ambulance Tasks
    taskStatus = xTaskCreate(Ambulance1_task, "Ambulance-1", TASK_STACK_SIZE, NULL, 3, &Ambulance1_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Ambulance1 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Ambulance2_task, "Ambulance-2", TASK_STACK_SIZE, NULL, 3, &Ambulance2_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Ambulance2 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Ambulance3_task, "Ambulance-3", TASK_STACK_SIZE, NULL, 3, &Ambulance3_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Ambulance3 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Ambulance4_task, "Ambulance-4", TASK_STACK_SIZE, NULL, 3, &Ambulance4_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Ambulance4 task!\n");
        while(1);
    }

    // Create Fire Tasks
    taskStatus = xTaskCreate(Fire1_task, "Fire-1", TASK_STACK_SIZE, NULL, 3, &Fire1_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Fire1 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Fire2_task, "Fire-2", TASK_STACK_SIZE, NULL, 3, &Fire2_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Fire2 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Fire3_task, "Fire-3", TASK_STACK_SIZE, NULL, 3, &Fire3_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Fire3 task!\n");
        while(1);
    }

    // Create COVID Tasks
    taskStatus = xTaskCreate(Covid1_task, "Covid-1", TASK_STACK_SIZE, NULL, 2, &Covid1_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Covid1 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Covid2_task, "Covid-2", TASK_STACK_SIZE, NULL, 2, &Covid2_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Covid2 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Covid3_task, "Covid-3", TASK_STACK_SIZE, NULL, 2, &Covid3_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Covid3 task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Covid4_task, "Covid-4", TASK_STACK_SIZE, NULL, 2, &Covid4_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Covid4 task!\n");
        while(1);
    }

    printf("All queues, semaphores, and tasks created successfully!\n");

    // Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // Should never reach here if scheduler starts successfully
    printf("ERROR: Scheduler failed to start!\n");
    while(1);

    return 0;
}

