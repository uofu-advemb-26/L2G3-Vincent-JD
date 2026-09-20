#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "pico/cyw43_arch.h"
#include "helpers.h"

void setUp(void) {}

void tearDown(void) {}

void test_LED_on(void) {
    printf("Now testing LED power-on.\n");
    bool state = 1;
    led_set(state);
    bool actual = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
    TEST_ASSERT_EQUAL_MESSAGE(state, actual, "LED should be turned on.");
}

void test_LED_off(void) {
    printf("Now testing LED power-off.\n");
    bool state = 1;
    led_set(state);
    bool actual = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
    TEST_ASSERT_EQUAL_MESSAGE(state, actual, "LED should be turned off.");
}

void test_LED_toggle(void) {
    printf("Now testing automated LED toggle.\n");
    bool on = 0;
    led_set(on);
    int count = 0;
    for(int i = 0; i < 128; i++) {
        int currentCount = count;
        bool currentState = led_toggle(on, &count, 11);
        TEST_ASSERT_EQUAL_MESSAGE(currentCount + 1, count, "Variable \"count\" should have incremented!");
        if((i + 1) % 11) {
            TEST_ASSERT_NOT_EQUAL_MESSAGE(on, currentState, "LED state mismatch! LED should be toggled!");
        }
        else {
            TEST_ASSERT_EQUAL_MESSAGE(on, currentState, "LED state mismatch! LED should not be toggled!");
        }
        on = currentState;
    }
    
}

void blank_test(void) {
    printf("This is a test. If you see this message then the blank test has succeeded.\n");
}

/**
 * Tests character conversion
 */
void char_test(void) {
    char convertedChar;

    //non-alphabeticals
    for(int i = 0; i < 65; i++) {
        convertedChar = debug_char_convert(i);
        TEST_ASSERT_EQUAL_CHAR_MESSAGE(i, convertedChar, "Character conversion failure! Character should remain the same!");
    }
    for(int i = 91; i < 97; i++) {
        convertedChar = debug_char_convert(i);
        TEST_ASSERT_EQUAL_CHAR_MESSAGE(i, convertedChar, "Character conversion failure! Character should remain the same!");
    }
    for(int i = 123; i <= 127; i++) {
        convertedChar = debug_char_convert(i);
        TEST_ASSERT_EQUAL_CHAR_MESSAGE(i, convertedChar, "Character conversion failure! Character should remain the same!");
    }

    //capital letters A-Z
    for(int i = 65; i <= 90; i++) {
        convertedChar = debug_char_convert(i);
        TEST_ASSERT_EQUAL_CHAR_MESSAGE(i + 32, convertedChar, "Character conversion failure! Uppercase should have been converted to lowercase!");
    }

    //lowercase letters A-Z
    for(int i = 97; i <= 122; i++) {
        // printf("char: %c    ", i);
        convertedChar = char_convert(i);
        // printf("converted char: %c  ", convertedChar);
        TEST_ASSERT_EQUAL_CHAR_MESSAGE(i - 32, convertedChar, "Character conversion failure! Lowercase should have been converted to uppercase!");
    }
    printf("\n");   //so that the "test pass" stuff appears on a separate line
}

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        // fflush(stdout);
        printf("End Tests\n");
        RUN_TEST(blank_test);
        RUN_TEST(test_LED_on);
        RUN_TEST(test_LED_off);
        RUN_TEST(test_LED_toggle);
        RUN_TEST(char_test);
        // sleep_ms(5000);
        UNITY_END();
    }
}
