#ifndef __DD_Task_H
#define __DD_Task_H

#include <stdint.h>
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../../FreeRTOS_Source/include/task.h"

typedef enum {
	Periodic,
	Aperiodic
} task_type;

typedef struct dd_task {
TaskHandle_t t_handle;
task_type type;
uint32_t task_id;
uint32_t release_time;
uint32_t absolute_deadline;
uint32_t completion_time;
} dd_task;

#endif /*__DD_Task_H*/


