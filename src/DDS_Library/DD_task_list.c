#include "DD_task_list.h"
#include <stdio.h>
#include <stdlib.h>

dd_task_lists* init_task_lists(void){
    dd_task_lists *task_lists = (dd_task_lists*)malloc(sizeof(dd_task_lists));

    task_lists->active_task_list = (dd_task_list*)malloc(sizeof(dd_task_list));
    task_lists->active_task_list->head = NULL;

    task_lists->complete_task_list = (dd_task_list*)malloc(sizeof(dd_task_list));
    task_lists->complete_task_list->head = NULL;

    task_lists->overdue_task_list = (dd_task_list*)malloc(sizeof(dd_task_list));
    task_lists->overdue_task_list->head = NULL;

    task_lists->current_task = NULL;

    return task_lists;
}

dd_task_list_node* init_task_list_node(dd_task task){
    dd_task_list_node *task_list = (dd_task_list_node*)malloc(sizeof(dd_task_list_node));
    task_list->task = task;
    task_list->next = NULL;
    return task_list;
}

dd_task create_dd_task(TaskHandle_t t_handle, task_type type, uint32_t task_id, uint32_t absolute_deadline){
    dd_task task;
    task.t_handle = t_handle;
    task.type = type;
    task.task_id = task_id;
    task.absolute_deadline = absolute_deadline;
    task.release_time = -1;
    task.completion_time = -1;
    return task;
}

void add_task_to_list_by_deadline(dd_task_list* task_list, dd_task task){

    dd_task_list_node *task_node = init_task_list_node(task);

    if(task_list->head == NULL){
        task_list->head = task_node;
    } else {

        dd_task_list_node *current_node = task_list->head;

        //If the front of the list needs to be replaced
        if(current_node->task.absolute_deadline > task_node->task.absolute_deadline){
            task_node->next = current_node;
            task_list->head = task_node;
            return;
        }

        // add to the list based on the absolute deadline
        while(current_node->next != NULL && current_node->next->task.absolute_deadline < task_node->task.absolute_deadline){
            current_node = current_node->next;
        }

        if(current_node->next == NULL){
            current_node->next = task_node;
        } else {
            task_node->next = current_node->next;
            current_node->next = task_node;
        }

    }
}

void add_task_to_list(dd_task_list* task_list, dd_task task){

    dd_task_list_node *task_node = init_task_list_node(task);

    if(task_list->head == NULL){
        task_list->head = task_node;
    } else {
        dd_task_list_node *current_node = task_list->head;
        while(current_node->next != NULL){
            current_node = current_node->next;
        }
        current_node->next = task_node;
    }
}

void remove_task(dd_task_list* task_list, uint32_t task_id){

    dd_task_list_node *current_node = task_list->head;

    if(current_node->task.task_id == task_id){
        task_list->head = current_node->next;
        free(current_node);
        return;
    }

    while(current_node->next != NULL){
        if(current_node->next->task.task_id == task_id){
            dd_task_list_node *temp = current_node->next;
            current_node->next = current_node->next->next;
            free(temp);
            return;
        }
        current_node = current_node->next;
    }

    fputs("Task not found in active task list", stderr);
}

dd_task get_earilest_task(dd_task_list* task_list){
    dd_task_list_node *current_node = task_list->head;

    if(current_node == NULL){
    	dd_task d;
    	d.task_id = -1;
        return d;
    }else{
        return (current_node->task);
    }
}

void print_task_list(dd_task_list* task_list){
    dd_task_list_node *current_node = task_list->head;
    while(current_node != NULL){
        printf("Task ID: %lu, Absolute Deadline: %lu\n", current_node->task.task_id, current_node->task.absolute_deadline);
    }
}
