#include "DD_scheduler.h"
QueueHandle_t dd_message_queue;

void DD_scheduler_initialize(void){
	//printf("Initializing Queue for generator and scheduler: Starting\n");
	dd_message_queue = xQueueCreate(25, sizeof(dd_message));
    vQueueAddToRegistry(dd_message_queue,"Scheduler Queue");
    //printf("Initializing Queue for generator and scheduler: Done\n");
}

void DD_scheduler_send_message(dd_message message){
	if( xQueueSend(dd_message_queue, &message, portMAX_DELAY ) != pdPASS ) {
		//printf("Couldn't send message!\n");
	    return;
	}
}

void handleOverDueTasks(dd_task_lists* task_lists){
	dd_task_list* active = task_lists->active_task_list;
	dd_task_list_node* current = active->head;
	TickType_t current_time = xTaskGetTickCount();

	while(current != NULL){

		if(current->task.relative_deadline < current_time){
			dd_task_list_node* overDueNode = remove_task(active, current->task.task_id);
			//printf("\nTask %d was overdue, removing it from processing\n", (int)overDueNode->task.task_id);
			add_task_to_list(task_lists->overdue_task_list, overDueNode->task);
			vTaskDelete(overDueNode->task.t_handle);
		}
		current = current->next;
	}
}

void DD_scheduler(void* parameters){
	dd_task_lists* task_lists = init_task_lists();
	dd_message queue_message;

	while(1){
		if( xQueueReceive( dd_message_queue, (void*)&queue_message, portMAX_DELAY ) == pdTRUE ){
			TickType_t current_time = xTaskGetTickCount();
			//printf("%d Scheduler: Received a message", (int)current_time);
			handleOverDueTasks(task_lists);
			if(queue_message.message == release_dd_task){
				//printf(" to release task with id %d\n", (int)queue_message.data.task_id);
				dd_task task = queue_message.data;
				task.relative_deadline = current_time + task.absolute_deadline;
				task.release_time = xTaskGetTickCount();

				add_task_to_list_by_deadline(task_lists->active_task_list, task);

				vTaskResume(queue_message.data.t_handle);
			}
			else if(queue_message.message == complete_dd_task){
				dd_task_list_node* completed_task = remove_task(task_lists->active_task_list, queue_message.data.task_id);

				completed_task->task.completion_time = xTaskGetTickCount() - completed_task->task.release_time ;
				add_task_to_list(task_lists->complete_task_list, completed_task->task);

				//printf(" to complete a task with id %d: took %d\n", queue_message.data.task_id, completed_task->task.completion_time);
				vTaskDelete(completed_task->task.t_handle);
			}
			else if(queue_message.message == get_active_dd_task_list){
				printf("\n\n\nActive List ------------- \n");
				print_task_list(task_lists->active_task_list);
			}
			else if(queue_message.message == get_completed_dd_task_list){
				printf("Complete List ------------- \n");
				print_task_list(task_lists->complete_task_list);
			}
			else if(queue_message.message == get_overdue_dd_task_list){
				printf("Overdue List ------------- \n");
				print_task_list(task_lists->overdue_task_list);
			}else {
				printf(stderr, "Invalid message type\n");
				return;
			}

		}
	}
}
