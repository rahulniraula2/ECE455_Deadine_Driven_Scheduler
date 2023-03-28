#include "DD_task_generators.h"

#define execution_time_task_1 200
#define execution_time_task_2 200
#define execution_time_task_3 200

#define period_1 500
#define period_2 500
#define period_3 500

dd_task DD_Create_vTask(TaskHandle_t *task_handle, TaskFunction_t task_function, char *task_name, uint32_t stack_size, void *pvParameters, UBaseType_t uxPriority, int task_id, int deadline){
    int task_id_computed = task_id;
	xTaskCreate(task_function, task_name, stack_size,(void*)task_id_computed , uxPriority, task_handle);
    vTaskSuspend(*task_handle);
    dd_task t = create_dd_task(*task_handle, Periodic, task_id_computed, pdMS_TO_TICKS(deadline));
    return t;
}

void DD_Task_Generator_1( void *pvParameters ){
    // Create a task
	int task_id = 1001;
    while(1){
    	//printf("Generator: Generating Task 1\n");
        dd_task taskCreated = DD_Create_vTask(&DD_task_1, task_1, "task_1", 130, NULL, 1, task_id++, period_1);
        dd_message release_message = {
            release_dd_task, // message type
            taskCreated, // task data
            xTaskGetCurrentTaskHandle() // task handle
        };
        //printf("Generator: Sending Task Message To Scheduler 1\n");
        DD_scheduler_send_message(release_message);
        vTaskDelay(pdMS_TO_TICKS(period_1));
    }
}

void simulateTaskFor(int timeInMS){
	TickType_t totalTicks = pdMS_TO_TICKS(timeInMS);
	TickType_t doneTime = 0;
	TickType_t start = xTaskGetTickCount();
	int a = 0;
	int b = 2;

	while (doneTime < totalTicks){

		for(int i=0;i<10000;i++){
			int c = a+b;
		}

		doneTime = xTaskGetTickCount() - start;
	}
}

void task_1 ( void *pvParameters ){
	int taskID = (int)pvParameters;
	while(1){

		simulateTaskFor(execution_time_task_1);

		dd_task d;
		d.task_id = taskID;
		dd_message complete_message = {
				complete_dd_task, // message type
		        d, // task data
		        xTaskGetCurrentTaskHandle() // task handle
		};

		//printf("Task 1: Task completed processing %d\n", taskID);
		DD_scheduler_send_message(complete_message);

		vTaskDelay(10000);
	}
}

void DD_Task_Generator_2( void *pvParameters ){
    // Create a task
	int task_id = 2001;
    while(1){
    	//printf("Generator: Generating Task 2\n");
        dd_task taskCreated = DD_Create_vTask(&DD_task_2, task_2, "task_2", 130, NULL, 1, task_id++, period_2);
        dd_message release_message = {
            release_dd_task, // message type
            taskCreated, // task data
            xTaskGetCurrentTaskHandle() // task handle
        };

        //printf("Generator: Sending Task Message To Scheduler 2\n");

        DD_scheduler_send_message(release_message);

        vTaskDelay(pdMS_TO_TICKS(period_2));
    }
}



void task_2 ( void *pvParameters ){
	int taskID = (int)pvParameters;
	while(1){
		simulateTaskFor(execution_time_task_2);
		dd_task d;
		d.task_id = taskID;
		dd_message complete_message = {
				complete_dd_task, // message type
		        d, // task data
		        xTaskGetCurrentTaskHandle() // task handle
		};

		//printf("Task 2: Task completed processing %d\n", taskID);
		DD_scheduler_send_message(complete_message);
		vTaskDelay(10000);
	}
}

void DD_Task_Generator_3( void *pvParameters ){
    // Create a task
	int task_id = 3001;
    while(1){
    	//printf("Generator: Generating Task 3\n");
        dd_task taskCreated = DD_Create_vTask(&DD_task_3, task_3, "task_3", 130, NULL, 1, task_id++, period_3);
        dd_message release_message = {
            release_dd_task, // message type
            taskCreated, // task data
            xTaskGetCurrentTaskHandle()
        };

        //printf("Generator: Sending Task release message To Scheduler 3\n");

        DD_scheduler_send_message(release_message);

        vTaskDelay(pdMS_TO_TICKS(period_3));
    }
}

void task_3 ( void *pvParameters ){
	int taskID = (int)pvParameters;
	while(1){
		simulateTaskFor(execution_time_task_3);
		dd_task d;
		d.task_id = taskID;
		dd_message complete_message = {
				complete_dd_task, // message type
		        d, // task data
		        xTaskGetCurrentTaskHandle() // task handle
		};

		//printf("Task 3: Task completed processing %d\n", taskID);
		DD_scheduler_send_message(complete_message);
		vTaskDelay(10000);
	}
}



