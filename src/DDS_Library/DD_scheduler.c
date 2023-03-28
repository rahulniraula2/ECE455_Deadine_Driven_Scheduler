#include "DD_scheduler.h"

static TaskHandle_t scheduler_task_handle;
static QueueHandle_t dd_message_queue;

dd_task_lists* DD_scheduler_initialize(void ){
	//TODO: double check queue creation
	scheduler_task_handle = xQueueCreate(1000, sizeof(dd_message));
    vQueueAddToRegistry(scheduler_task_handle,"Scheduler Queue");

	return init_task_lists();
}

void DD_scheduler_start(void){
	xTaskCreate(DD_scheduler, "DD_scheduler", 1000, NULL, 1000, &scheduler_task_handle);
}

void DD_scheduler(void){
	dd_task_lists* task_lists = DD_scheduler_initialize();

	dd_message queue_message;

	while(1){
		if( xQueueReceive( dd_message_queue, (void*)&queue_message, portMAX_DELAY ) == pdTRUE ){
			if(queue_message.message == release_dd_task){
				dd_task task = queue_message.data;
				add_task_to_list_by_deadline(task_lists->active_task_list, task);
			}
			else if(queue_message.message == complete_dd_task){
				remove_task(task_lists->active_task_list, queue_message.data.task_id);
			}
			else if(queue_message.message == get_completed_dd_task_list){
				print_task_list(task_lists->active_task_list);
			}
			else if(queue_message.message == get_overdue_dd_task_list){
				print_task_list(task_lists->overdue_task_list);
			}else {
				fprintf(stderr, "Invalid message type\n");
				exit(1);
			}

		}
	}
}

void schedule_tasks(dd_task_lists* task_lists){

	dd_task current_task;

	if(task_lists->current_task == NULL ){
		current_task = get_earilest_task(task_lists->active_task_list);
		if (current_task.task_id != -1)
		{
			task_lists->current_task = task_lists->active_task_list->head;
			task_lists->active_task_list->head = task_lists->active_task_list->head->next;
		}
	} else {
		current_task = task_lists->current_task->task;
	}


	

}
