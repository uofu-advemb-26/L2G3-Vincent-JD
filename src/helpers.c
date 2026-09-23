#include "helpers.h"
#include <stdio.h>

/**
 * LED setting wrapper function
 */
void led_set(bool state) {
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, state); 
    return;
}

/**
 * This should ensure that the LED only ever toggles if the count is NOT divisible by the value "divisibleBy"
 */
bool led_toggle(bool baseState, int* count, int divisibleBy) {
    *count += 1;
    bool nextState = *count % divisibleBy ? !baseState : baseState;
    led_set(nextState);
    return nextState;
}

/**
 * Character converter helper function for use in both debugging and for cleaning up hello_freertos.c
 * For the sake of retaining functionality, it is identical to the old code where it would've been slipped in place.
 */
char char_convert(char inChar) {
    if (inChar <= 'z' && inChar >= 'a') return(inChar - 32);            //if the char is between lowercase a and lowercase z, decrement ASCII code by 32
    else if (inChar >= 'A' && inChar <= 'Z') return(inChar + 32);       //if it's between uppercase A and Z, increment ASCII code by 32
    else return(inChar);                                                //if it's not an alphabetical character, don't modify
}

char debug_char_convert(char inChar) {
    printf("char: %c    ", inChar);
    char convertedChar = char_convert(inChar);
    printf("converted char: %c  ", convertedChar);
    return convertedChar;
}