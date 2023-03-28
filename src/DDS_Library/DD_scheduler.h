#ifndef DD_scheduler_H
#define DD_scheduler_H

#include <stdio.h>
#include "DD_task_list.h"
#include "DD_Task.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"


void DD_scheduler(void* parameters);
void DD_scheduler_initialize(void);
void DD_scheduler_send_message(dd_message message);


#endif  // __scheduler_H
