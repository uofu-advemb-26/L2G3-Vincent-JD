/**
 * Copyright (c) 2022 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "FreeRTOS.h"
#include "task.h"
#include "helpers.h"

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/cyw43_arch.h"

int count = 0;
bool on = false;

#define MAIN_TASK_PRIORITY      ( tskIDLE_PRIORITY + 1UL )
#define MAIN_TASK_STACK_SIZE configMINIMAL_STACK_SIZE


/**a separate function in which we do the LED blinking. it has been set up
 * such that the parameters from the old code can be tuned by hand.
 */

// void blinker(int countDivisibleBy, int delay) {
//     cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on); 
//     if(count++ % countDivisibleBy) on = !on;
//     vTaskDelay(delay);
// }

void blink_task(__unused void *params) {
    hard_assert(cyw43_arch_init() == PICO_OK);
    while (true) {      //runs forever blinking an LED
        // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on); 
        led_set(on);
        if (count++ % 11) on = !on;     //if the counter is divisible by 11, then turn off the LED to start the next blinky
        vTaskDelay(500);
        
        // blinker(11, 500);   //call the new LED blinker function with "divisible by 11" and a delay of 500 as parameters
    }
}

void main_task(__unused void *params) {
    /*Creates another task to blink an LED and splits that off
    */
    xTaskCreate(blink_task, "BlinkThread",
                BLINK_TASK_STACK_SIZE, NULL, BLINK_TASK_PRIORITY, NULL);

    /*Does some kind of ASCII manipulation, taking a character input and outputting it back to stdout 
    after some unspecified processing occurs
    */
    char c;
    while(c = getchar()) {
        if (c <= 'z' && c >= 'a') putchar(c - 32);      //if the char is between lowercase a and lowercase z, decrement ASCII code by 32
        else if (c >= 'A' && c <= 'Z') putchar(c + 32); //if it's between uppercase A and Z, increment ASCII code by 32
        else putchar(c);                                //if it's not an alphabetical character, don't modify
    }
}

int main( void )
{
    stdio_init_all();
    const char *rtos_name;
    rtos_name = "FreeRTOS";
    TaskHandle_t task;

    /*this creates a new thread running the function "main_task". 
    It sets up a maximum stack, passes parameters, sets the task priority, and sets a pointer to the created task*/
    xTaskCreate(main_task, "MainThread",
                MAIN_TASK_STACK_SIZE, NULL, MAIN_TASK_PRIORITY, &task);
    vTaskStartScheduler();
    return 0;
}
