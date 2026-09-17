#include "helpers.h"
#include <stdio.h>

void led_set(bool state) {
    printf("Entering LED set function");
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state); 
}

void led_toggle(void) {

}