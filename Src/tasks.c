/**
 * @file tasks.c
 * @brief Task implementations for City Emergency Dispatch System
 *
 * Contains all FreeRTOS task implementations for the emergency dispatch
 * simulation, including department resource tasks, dispatcher, event
 * generator, and logger.
 */

#include "tasks.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include <stdio.h>
#include <stdlib.h>

/* ============================================================================
 * External References to Global Variables (Defined in main.c)
 * ============================================================================
 */

/* Queue Handles */
extern QueueHandle_t xDispatcherQueue;
extern QueueHandle_t xPoliceQueue;
extern QueueHandle_t xAmbulanceQueue;
extern QueueHandle_t xFireQueue;
extern QueueHandle_t xCovidQueue;
extern QueueHandle_t xLoggerQueue;

/* Semaphore Handles */
extern SemaphoreHandle_t xPoliceSemaphore;
extern SemaphoreHandle_t xAmbulanceSemaphore;
extern SemaphoreHandle_t xFireSemaphore;
extern SemaphoreHandle_t xCovidSemaphore;

/* Event Counter */
extern int counter;

/* ============================================================================
 * Police Department Tasks
 * ============================================================================
 * Police department has 3 resources to handle incidents.
 * Each task represents one police unit/vehicle.
 */

void Police1_task(void *pvParameters) {
    Event_t event;
    while(1) {
        /* Wait for an event from the police queue */
        xQueueReceive(xPoliceQueue, &event, portMAX_DELAY);

        /* Acquire police resource (semaphore) */
        xSemaphoreTake(xPoliceSemaphore, portMAX_DELAY);

        /* Simulate handling the event (1-3 seconds) */
        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Police-1 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Police-1 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);

        /* Send event to logger for tracking */
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);

        /* Release police resource */
        xSemaphoreGive(xPoliceSemaphore);
    }
}

void Police2_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xPoliceQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xPoliceSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Police-2 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Police-2 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xPoliceSemaphore);
    }
}

void Police3_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xPoliceQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xPoliceSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Police-3 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Police-3 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xPoliceSemaphore);
    }
}

/* ============================================================================
 * Ambulance Department Tasks
 * ============================================================================
 * Ambulance department has 4 resources for medical emergencies.
 * Each task represents one ambulance unit.
 */

void Ambulance1_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xAmbulanceQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xAmbulanceSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Ambulance-1 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Ambulance-1 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xAmbulanceSemaphore);
    }
}

void Ambulance2_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xAmbulanceQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xAmbulanceSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Ambulance-2 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Ambulance-2 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xAmbulanceSemaphore);
    }
}

void Ambulance3_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xAmbulanceQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xAmbulanceSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Ambulance-3 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Ambulance-3 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xAmbulanceSemaphore);
    }
}

void Ambulance4_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xAmbulanceQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xAmbulanceSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Ambulance-4 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Ambulance-4 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xAmbulanceSemaphore);
    }
}

/* ============================================================================
 * Fire Department Tasks
 * ============================================================================
 * Fire department has 3 resources for fire emergencies.
 * Each task represents one fire truck unit.
 */

void Fire1_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xFireQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xFireSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Fire-1 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Fire-1 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xFireSemaphore);
    }
}

void Fire2_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xFireQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xFireSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Fire-2 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Fire-2 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xFireSemaphore);
    }
}

void Fire3_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xFireQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xFireSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Fire-3 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Fire-3 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xFireSemaphore);
    }
}

/* ============================================================================
 * COVID Department Tasks
 * ============================================================================
 * COVID department has 4 resources for COVID-19 related emergencies.
 * Each task represents one COVID response unit.
 */

void Covid1_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xCovidQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xCovidSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Covid-1 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Covid-1 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xCovidSemaphore);
    }
}

void Covid2_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xCovidQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xCovidSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Covid-2 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Covid-2 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xCovidSemaphore);
    }
}

void Covid3_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xCovidQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xCovidSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Covid-3 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Covid-3 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xCovidSemaphore);
    }
}

void Covid4_task(void *pvParameters) {
    Event_t event;
    while(1) {
        xQueueReceive(xCovidQueue, &event, portMAX_DELAY);
        xSemaphoreTake(xCovidSemaphore, portMAX_DELAY);

        uint32_t duration_ms = 1000 + rand() % 2000;
        printf("START: Covid-4 handling event ID=[%lu]\n", (unsigned long)event.event_id);

        vTaskDelay(pdMS_TO_TICKS(duration_ms));

        printf("COMPLETE: Covid-4 finished event ID=[%lu] after %lums\n",
               (unsigned long)event.event_id, (unsigned long)duration_ms);
        xQueueSend(xLoggerQueue, &event, portMAX_DELAY);
        xSemaphoreGive(xCovidSemaphore);
    }
}

/* ============================================================================
 * Dispatcher Task
 * ============================================================================
 * Central dispatcher that routes emergency events to appropriate departments
 * based on event type codes.
 */

void Dispatcher_task(void *pvParameters) {
    Event_t event;

    while (1) {
        /* Receive event from central dispatcher queue */
        xQueueReceive(xDispatcherQueue, &event, portMAX_DELAY);

        /* Route event to appropriate department queue based on type */
        switch(event.event_type) {
            case EVENT_POLICE:
                xQueueSend(xPoliceQueue, &event, portMAX_DELAY);
                break;
            case EVENT_AMBULANCE:
                xQueueSend(xAmbulanceQueue, &event, portMAX_DELAY);
                break;
            case EVENT_FIRE:
                xQueueSend(xFireQueue, &event, portMAX_DELAY);
                break;
            case EVENT_COVID:
                xQueueSend(xCovidQueue, &event, portMAX_DELAY);
                break;
            default:
                /* Invalid event type - could log error here */
                break;
        }
    }
}

/* ============================================================================
 * Logger Task
 * ============================================================================
 * Logs all completed events for tracking and analysis.
 * Receives events from department tasks after completion.
 */

void Logger_task(void *pvParameters) {
    Event_t event;

    while(1) {
        /* Receive completed event from logger queue */
        xQueueReceive(xLoggerQueue, &event, portMAX_DELAY);

        /* Log event information based on type */
        switch(event.event_type) {
            case EVENT_POLICE:
                printf("EVENT_POLICE (ID=[%lu], Priority=%d)\n",
                       (unsigned long)event.event_id, (int)event.priority);
                break;
            case EVENT_AMBULANCE:
                printf("EVENT_AMBULANCE (ID=[%lu], Priority=%d)\n",
                       (unsigned long)event.event_id, (int)event.priority);
                break;
            case EVENT_FIRE:
                printf("EVENT_FIRE (ID=[%lu], Priority=%d)\n",
                       (unsigned long)event.event_id, (int)event.priority);
                break;
            case EVENT_COVID:
                printf("EVENT_COVID (ID=[%lu], Priority=%d)\n",
                       (unsigned long)event.event_id, (int)event.priority);
                break;
            default:
                break;
        }
    }
}

/* ============================================================================
 * Event Generator Task
 * ============================================================================
 * Generates random emergency events at 1-5 second intervals.
 * Assigns priority based on event criticality:
 *   - Fire & Ambulance: Priority 3 (life-threatening)
 *   - Police: Priority 2 (urgent)
 *   - COVID: Priority 1 (important but less urgent)
 */

void Event_generator_task(void *pvParameters) {
    Event_t event;

    while(1) {
        /* Generate event with unique ID */
        event.event_id = counter++;

        /* Randomly select event type (1-4) */
        event.event_type = (rand() % 4 + 1);

        /* Assign priority based on event type */
        switch(event.event_type) {
            case EVENT_FIRE:
                event.priority = 3;  /* Highest - life-threatening */
                break;
            case EVENT_AMBULANCE:
                event.priority = 3;  /* Highest - medical emergency */
                break;
            case EVENT_POLICE:
                event.priority = 2;  /* Medium - urgent but not life-threatening */
                break;
            case EVENT_COVID:
                event.priority = 1;  /* Lower - can wait slightly */
                break;
            default:
                event.priority = 1;  /* Default low priority */
                break;
        }

        /* Send event to dispatcher */
        xQueueSend(xDispatcherQueue, &event, portMAX_DELAY);

        /* Wait random interval (1-5 seconds) before next event */
        vTaskDelay(pdMS_TO_TICKS(1000 + rand() % 4000));
    }
}
