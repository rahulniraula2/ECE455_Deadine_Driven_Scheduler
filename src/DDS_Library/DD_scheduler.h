#ifndef DD_scheduler_H
#define DD_scheduler_H

#include <stdio.h>
#include "DD_task_list.h"
#include "DD_Task.h"
#include "../FreeRTOS_Source/include/FreeRTOS.h"
#include "../FreeRTOS_Source/include/queue.h"

void DD_scheduler_start(void);

void add_to_active_list(dd_task task);/*{
    add_task_to_list_by_deadline(task_lists->active_task_list, task);
}*/

void add_to_complete_list(dd_task task);/*{
    add_task_to_list(task_lists->complete_task_list, task);
}*/

void add_to_overdue_list(dd_task task);/*{
    add_task_to_list(task_lists->overdue_task_list, task);
}*/



#endif  // __scheduler_H
