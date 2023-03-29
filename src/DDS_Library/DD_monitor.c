#include "DD_monitor.h"


void DD_monitor( void *pvParameters ){
	dd_message message;
	while(1){
		vTaskDelay(1500);
		message.message = get_active_dd_task_list;
		DD_scheduler_send_message(message);
		vTaskDelay(30);
		message.message = get_completed_dd_task_list;
		DD_scheduler_send_message(message);
		vTaskDelay(30);
		message.message = get_overdue_dd_task_list;
		DD_scheduler_send_message(message);

		vTaskDelay(150000);
	}
}
