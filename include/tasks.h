#include <stdio.h>

#include <FreeRTOS.h>
#include <task.h>

#include <pico/stdlib.h>
#include <pico/multicore.h>
#include <pico/cyw43_arch.h>
#include "helpers.h"

void blink_task(__unused void *params);

void main_task(__unused void *params);