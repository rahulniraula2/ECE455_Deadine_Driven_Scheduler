#include "scheduler.h"

dd_task_lists *task_lists;

void DD_scheduler_initialize(void ){
    dd_task_lists *task_lists = init_task_lists();
}

void DD_scheduler_start(void){

}