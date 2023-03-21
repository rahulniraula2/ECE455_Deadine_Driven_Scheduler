#ifndef __scheduler_H
#define __scheduler_H

#include "DD_task_list.h"

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
