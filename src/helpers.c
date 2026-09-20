#include "helpers.h"
#include <stdio.h>

void led_set(bool state) {
    printf("Entering LED set function\n");
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state); 
    return;
}

/**
 * This should ensure that the LED only ever toggles if the count is NOT divisible by the value "divisibleBy"
 */
bool led_toggle(bool baseState, int* count, int divisibleBy) {
    *count += 1;
    bool nextState = *count % divisibleBy ? !baseState : baseState;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, nextState); 
    return nextState;
}