#ifndef __DD_task_list_H
#define __DD_task_list_H

#include "DD_Task.h"

typedef struct dd_task_list_node {
    dd_task task;
    dd_task_list_node *next;
} dd_task_list_node;

typedef struct dd_task_list {
    char name[20];
    dd_task_list_node *head;
} dd_task_list;

typedef struct dd_task_lists {
    dd_task_list *active_task_list;
    dd_task_list *complete_task_list;
    dd_task_list *overdue_task_list;
} dd_task_lists;

dd_task_lists* init_task_lists(void);

void add_task_to_list_by_deadline(dd_task_list* task_list, dd_task task);
void add_task_to_list(dd_task_list* task_list, dd_task task);
dd_task get_earilest_task(dd_task_list* task_list);
void remove_task(dd_task_list* task_list, uint32_t task_id);

void print_task_list(dd_task_list* task_list);

#endif
