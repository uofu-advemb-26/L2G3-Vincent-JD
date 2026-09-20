#ifndef _HELPERS_H_
#define _HELPERS_H_

#include "FreeRTOS.h"
#include "task.h"

//set the priority and stack size of the blink task
#define BLINK_TASK_PRIORITY     ( tskIDLE_PRIORITY + 2UL )
#define BLINK_TASK_STACK_SIZE configMINIMAL_STACK_SIZE

void led_set(bool state);
bool led_toggle(bool baseState, int *count, int divisibleBy);

#endif