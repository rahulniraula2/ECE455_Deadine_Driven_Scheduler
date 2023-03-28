#ifndef DD_TASK_GENERATORS_H_
#define DD_TASK_GENERATORS_H_

#include <stdint.h>
#include "DD_task_list.h"
#include "DD_Task.h"DD


TaskHandle_t DD_task_1;
TaskHandle_t DD_task_2;
TaskHandle_t DD_task_3;
TaskHandle_t DD_task_AP_4;

void PeriodicTask_1 ( void *pvParameters );
void DD_Task_Generator_1( void *pvParameters );
void PeriodicTask_2 ( void *pvParameters );
void DD_Task_Generator_2( void *pvParameters );
void PeriodicTask_3 ( void *pvParameters );
void DD_Task_Generator_3( void *pvParameters );

void EXTI0_IRQHandler(void);
void AperiodicTask_1( void *pvParameters );
void AperiodicTaskGenerator( void *pvParameters );


#endif /* DD_TASK_GENERATORS_H_ */