/**
 * @file main.c
 * @brief Main initialization and configuration for City Emergency Dispatch System
 *
 * This file contains the main entry point and system initialization including:
 * - Global variable declarations (queues, semaphores, task handles)
 * - Queue creation for inter-task communication
 * - Semaphore creation for resource management
 * - Task creation for all system components
 * - FreeRTOS scheduler startup
 *
 * @author Nadav
 * @date 2026
 */

#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "init.h"
#include "emergency_dispatch.h"
#include "semphr.h"
#include "tasks.h"

/* ============================================================================
 * Configuration
 * ============================================================================
 */
#define TASK_STACK_SIZE  configMINIMAL_STACK_SIZE

/* ============================================================================
 * Global Variables
 * ============================================================================
 */

/* Event counter for unique event IDs */
int counter = 0;

/* ============================================================================
 * Task Handles
 * ============================================================================
 * Handles allow us to reference and control tasks after creation.
 * Set to NULL initially, populated by xTaskCreate().
 */

/* Core System Tasks */
TaskHandle_t Event_generator_handler = NULL;
TaskHandle_t Logger_handler = NULL;
TaskHandle_t Dispatcher_handler = NULL;

/* Police Department Tasks (3 resources) */
TaskHandle_t Police1_handler = NULL;
TaskHandle_t Police2_handler = NULL;
TaskHandle_t Police3_handler = NULL;

/* Ambulance Department Tasks (4 resources) */
TaskHandle_t Ambulance1_handler = NULL;
TaskHandle_t Ambulance2_handler = NULL;
TaskHandle_t Ambulance3_handler = NULL;
TaskHandle_t Ambulance4_handler = NULL;

/* Fire Department Tasks (3 resources) */
TaskHandle_t Fire1_handler = NULL;
TaskHandle_t Fire2_handler = NULL;
TaskHandle_t Fire3_handler = NULL;

/* COVID Department Tasks (4 resources) */
TaskHandle_t Covid1_handler = NULL;
TaskHandle_t Covid2_handler = NULL;
TaskHandle_t Covid3_handler = NULL;
TaskHandle_t Covid4_handler = NULL;

/* ============================================================================
 * Queue Handles
 * ============================================================================
 * Queues provide thread-safe inter-task communication.
 * Messages (Event_t structures) are passed between tasks via queues.
 */

QueueHandle_t xDispatcherQueue = NULL;   /* Central queue for all incoming events */
QueueHandle_t xPoliceQueue = NULL;       /* Police department event queue */
QueueHandle_t xFireQueue = NULL;         /* Fire department event queue */
QueueHandle_t xAmbulanceQueue = NULL;    /* Ambulance department event queue */
QueueHandle_t xCovidQueue = NULL;        /* COVID department event queue */
QueueHandle_t xLoggerQueue = NULL;       /* Logger queue for completed events */

/* ============================================================================
 * Semaphore Handles
 * ============================================================================
 * Counting semaphores manage limited resources for each department.
 * Initial count = max count = number of available resources.
 */

SemaphoreHandle_t xPoliceSemaphore;      /* Police resources (3 units) */
SemaphoreHandle_t xAmbulanceSemaphore;   /* Ambulance resources (4 units) */
SemaphoreHandle_t xFireSemaphore;        /* Fire resources (3 units) */
SemaphoreHandle_t xCovidSemaphore;       /* COVID resources (4 units) */

/* ============================================================================
 * Main Function
 * ============================================================================
 */

int main(void) {
    /* Initialize FreeRTOS platform-specific settings */
    init_main();

    /* ========================================================================
     * Create Queues
     * ========================================================================
     * Queues allow tasks to communicate by passing Event_t structures.
     */
    xDispatcherQueue = xQueueCreate(DISPATCHER_QUEUE_LENGTH, sizeof(Event_t));
    xPoliceQueue = xQueueCreate(POLICE_QUEUE_LENGTH, sizeof(Event_t));
    xAmbulanceQueue = xQueueCreate(AMBULANCE_QUEUE_LENGTH, sizeof(Event_t));
    xFireQueue = xQueueCreate(FIRE_QUEUE_LENGTH, sizeof(Event_t));
    xCovidQueue = xQueueCreate(COVID_QUEUE_LENGTH, sizeof(Event_t));
    xLoggerQueue = xQueueCreate(LOGGER_QUEUE_LENGTH, sizeof(Event_t));

    /* Verify all queues were created successfully */
    if (xDispatcherQueue == NULL || xPoliceQueue == NULL ||
        xAmbulanceQueue == NULL || xFireQueue == NULL ||
        xCovidQueue == NULL || xLoggerQueue == NULL) {
        printf("ERROR: Failed to create queues!\n");
        while(1);  /* Halt execution */
    }

    /* ========================================================================
     * Create Semaphores
     * ========================================================================
     * Counting semaphores track available resources for each department.
     * Max count = initial count = number of resources available.
     */
    xPoliceSemaphore = xSemaphoreCreateCounting(NUM_POLICE, NUM_POLICE);
    xAmbulanceSemaphore = xSemaphoreCreateCounting(NUM_AMBULANCE, NUM_AMBULANCE);
    xFireSemaphore = xSemaphoreCreateCounting(NUM_FIRE, NUM_FIRE);
    xCovidSemaphore = xSemaphoreCreateCounting(NUM_COVID, NUM_COVID);

    /* Verify all semaphores were created successfully */
    if (xPoliceSemaphore == NULL || xAmbulanceSemaphore == NULL ||
        xFireSemaphore == NULL || xCovidSemaphore == NULL) {
        printf("ERROR: Failed to create semaphores!\n");
        while(1);  /* Halt execution */
    }

    /* ========================================================================
     * Create Tasks
     * ========================================================================
     * Create all FreeRTOS tasks with appropriate priorities:
     *   Priority 4: Dispatcher (highest - must route events quickly)
     *   Priority 3: Department resources (handle events)
     *   Priority 2: COVID resources (lower priority events)
     *   Priority 1: Event generator (generates work)
     *   Priority 0: Logger (lowest - logs after completion)
     */
    BaseType_t taskStatus;

    /* Core System Tasks */
    taskStatus = xTaskCreate(Dispatcher_task, "Dispatcher", TASK_STACK_SIZE, NULL, 4, &Dispatcher_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Dispatcher task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Event_generator_task, "Event_generator", TASK_STACK_SIZE, NULL, 1, &Event_generator_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Event Generator task!\n");
        while(1);
    }

    taskStatus = xTaskCreate(Logger_task, "Logger", TASK_STACK_SIZE, NULL, 0, &Logger_handler);
    if (taskStatus != pdPASS) {
        printf("ERROR: Failed to create Logger task!\n");
        while(1);
    }

    /* Police Department Tasks (3 resources) */
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

    /* Ambulance Department Tasks (4 resources) */
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

    /* Fire Department Tasks (3 resources) */
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

    /* COVID Department Tasks (4 resources) */
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

    /* All resources created successfully */
    printf("All queues, semaphores, and tasks created successfully!\n");

    /* ========================================================================
     * Start FreeRTOS Scheduler
     * ========================================================================
     * This function starts the FreeRTOS kernel and begins task execution.
     * It should NEVER return if successful.
     */
    vTaskStartScheduler();

    /* Should never reach here if scheduler starts successfully */
    printf("ERROR: Scheduler failed to start!\n");
    while(1);

    return 0;
}
