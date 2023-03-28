#ifndef DD_TASK_GENERATORS_H_
#define DD_TASK_GENERATORS_H_

#include <stdint.h>
#include "DD_scheduler.h"
#include "DD_task_list.h"
#include "DD_Task.h"


TaskHandle_t DD_task_1;
TaskHandle_t DD_task_2;
TaskHandle_t DD_task_3;

void task_1 ( void *pvParameters );
void task_2 ( void *pvParameters );
void task_3 ( void *pvParameters );

void DD_Task_Generator_1( void *pvParameters );
void DD_Task_Generator_2( void *pvParameters );
void DD_Task_Generator_3( void *pvParameters );


#endif /* DD_TASK_GENERATORS_H_ */
