/**
 * @file emergency_dispatch.h
 * @brief Core definitions and data structures for Emergency Dispatch System
 *
 * This header defines:
 * - Event types (police, ambulance, fire, COVID)
 * - Resource counts for each department
 * - Queue lengths for inter-task communication
 * - Event_t structure for emergency events
 */

#ifndef EMERGENCY_DISPATCH_H
#define EMERGENCY_DISPATCH_H

#include "FreeRTOS.h"
#include "queue.h"

/* ============================================================================
 * Event Type Definitions
 * ============================================================================
 * These codes identify the type of emergency event and determine which
 * department handles the event.
 */
#define EVENT_POLICE    1  /* Police emergency (crime, disturbance) */
#define EVENT_AMBULANCE 2  /* Medical emergency */
#define EVENT_FIRE      3  /* Fire emergency */
#define EVENT_COVID     4  /* COVID-19 related emergency */

/* ============================================================================
 * Department Resource Counts
 * ============================================================================
 * Number of available resources (vehicles/units) per department.
 * These define the maximum concurrent events each department can handle.
 */
#define NUM_POLICE      3  /* 3 police units available */
#define NUM_AMBULANCE   4  /* 4 ambulances available */
#define NUM_FIRE        3  /* 3 fire trucks available */
#define NUM_COVID       4  /* 4 COVID response units available */

/* ============================================================================
 * Queue Length Definitions
 * ============================================================================
 * Maximum number of events that can wait in each queue.
 * Larger queues prevent event loss during high load but use more RAM.
 */
#define LOGGER_QUEUE_LENGTH     30  /* Logger queue (collects from all departments) */
#define DISPATCHER_QUEUE_LENGTH 20  /* Central dispatcher queue (all incoming events) */
#define POLICE_QUEUE_LENGTH     10  /* Police department queue */
#define AMBULANCE_QUEUE_LENGTH  10  /* Ambulance department queue */
#define FIRE_QUEUE_LENGTH       10  /* Fire department queue */
#define COVID_QUEUE_LENGTH      10  /* COVID department queue */

/* ============================================================================
 * Event Structure Definition
 * ============================================================================
 */

/**
 * @struct Event_t
 * @brief Represents an emergency event in the system
 *
 * @param event_type Type of emergency (EVENT_POLICE, EVENT_AMBULANCE, etc.)
 * @param priority   Event priority (1=low, 2=medium, 3=high/critical)
 * @param event_id   Unique identifier for this event
 */
typedef struct {
    uint8_t  event_type;  /* Type of emergency (1-4) */
    uint8_t  priority;    /* Priority level (1-3) */
    uint32_t event_id;    /* Unique event identifier */
} Event_t;

#endif /* EMERGENCY_DISPATCH_H */