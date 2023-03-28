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
uint32_t relative_deadline;
uint32_t completion_time;
} dd_task;

typedef enum dd_messages
{
    release_dd_task,
    complete_dd_task,
    get_active_dd_task_list,
    get_completed_dd_task_list,
    get_overdue_dd_task_list

} dd_messages;

typedef struct dd_message
{
    dd_messages message;;
    dd_task data;
    TaskHandle_t task_handle;

} dd_message;

#endif /*__DD_Task_H*/


