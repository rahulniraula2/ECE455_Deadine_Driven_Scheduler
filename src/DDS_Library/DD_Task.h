#ifndef __DD_Task_H
#define __DD_Task_H

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

typedef struct dd_task_list {
dd_task task;
struct dd_task_list *next_task;
} dd_task_list;

#endif /*__DD_Task_H*/


