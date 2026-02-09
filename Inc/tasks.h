/**
 * @file tasks.h
 * @brief Task function declarations for City Emergency Dispatch System
 *
 * This header declares all FreeRTOS task functions used in the emergency
 * dispatch simulation, including department resource tasks, dispatcher,
 * event generator, and logger.
 */

#ifndef TASKS_H
#define TASKS_H

#include "emergency_dispatch.h"

/* ============================================================================
 * Department Resource Tasks
 * ============================================================================
 * Each department has multiple resource tasks that handle emergency events.
 * Tasks wait for events from their department queue, acquire a semaphore
 * (representing a resource), perform the task, and release the semaphore.
 */

/* Police Department Tasks (3 resources) */
void Police1_task(void *pvParameters);
void Police2_task(void *pvParameters);
void Police3_task(void *pvParameters);

/* Ambulance Department Tasks (4 resources) */
void Ambulance1_task(void *pvParameters);
void Ambulance2_task(void *pvParameters);
void Ambulance3_task(void *pvParameters);
void Ambulance4_task(void *pvParameters);

/* Fire Department Tasks (3 resources) */
void Fire1_task(void *pvParameters);
void Fire2_task(void *pvParameters);
void Fire3_task(void *pvParameters);

/* COVID Department Tasks (4 resources) */
void Covid1_task(void *pvParameters);
void Covid2_task(void *pvParameters);
void Covid3_task(void *pvParameters);
void Covid4_task(void *pvParameters);

/* ============================================================================
 * Core System Tasks
 * ============================================================================
 */

/**
 * @brief Dispatcher task - Routes events to appropriate departments
 *
 * Receives events from the central dispatcher queue and forwards them to
 * the appropriate department queue based on event type.
 */
void Dispatcher_task(void *pvParameters);

/**
 * @brief Logger task - Logs completed events
 *
 * Receives events from the logger queue and prints event information
 * including ID, type, and priority.
 */
void Logger_task(void *pvParameters);

/**
 * @brief Event generator task - Creates random emergency events
 *
 * Generates random emergency events at 1-5 second intervals and assigns
 * priority based on event type (Fire/Ambulance=3, Police=2, COVID=1).
 */
void Event_generator_task(void *pvParameters);

#endif /* TASKS_H */
