
#ifndef EMERGENCY_DISPATCH_H
#define EMERGENCY_DISPATCH_H

#include "FreeRTOS.h"
#include "queue.h"

// Event types
#define EVENT_POLICE    1
#define EVENT_AMBULANCE 2
#define EVENT_FIRE      3
#define EVENT_COVID     4

// Resource counts
#define NUM_POLICE      3
#define NUM_AMBULANCE   4
#define NUM_FIRE        2
#define NUM_COVID       4

#define LOGGER_QUEUE_LENGTH     30
#define DISPATCHER_QUEUE_LENGTH 20
#define POLICE_QUEUE_LENGTH     10
#define AMBULANCE_QUEUE_LENGTH  10
#define FIRE_QUEUE_LENGTH       10
#define COVID_QUEUE_LENGTH      10

typedef struct {
    uint8_t  event_type;
    uint8_t  priority;
    uint32_t event_id;
} Event_t;

#endif