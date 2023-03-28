#include "DD_task_generators.h"

dd_task DD_Create_vTask(TaskHandle_t *task_handle, TaskFunction_t task_function, char *task_name, uint32_t stack_size, void *pvParameters, UBaseType_t uxPriority){
    xTaskCreate(task_function, task_name, stack_size, pvParameters, uxPriority, task_handle);
    vTaskSuspend(DD_task_1);
    //current time
    dd_task t = create_dd_task(*task_handle, PERIODIC, 1, 1000);
    TickType_t current_time = xTaskGetTickCount();
    t.release_time = current_time;
    return t;
}

void DD_Task_Generator_1( void *pvParameters ){
    // Create a task
    while(1){
        dd_task taskCreated = DD_Create_vTask(&DD_task_1, PeriodicTask_1, "PeriodicTask_1", 1000, NULL, 1);

        dd_message release_message = {
            release_dd_task, // message type
            taskCreated, // task data
            xTaskGetCurrentTaskHandle() // task handle
        };

        if( xQueueSend(dd_message_queue, &create_task_message, portMAX_DELAY ) != pdPASS ) {
            printf("Couldn't create a task!\n");
            return 0;
        }

        vTaskDelay(3000);
    }
}

