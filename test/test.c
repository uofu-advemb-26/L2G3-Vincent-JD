#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "pico/cyw43_arch.h"
#include "helpers.h"

void setUp(void) {}

void tearDown(void) {}

void test_LED(void) {
    printf("Starting LED test\n");
    printf("Writing LED to state 0\n");
    // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false); 
    // cyw43_gpio_set(&cyw43_state, CYW43_WL_GPIO_LED_PIN, false);
    led_set(false);

    printf("Completed writing LED state 0\n");
    // TEST_ASSERT_TRUE_MESSAGE(cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN) == 0, "LED confirmed turned off");
    // printf("Attempting to force LED off\n");
    // int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN); 
    // TEST_ASSERT_MESSAGE(gpio == 0, "LED successfully turned off");
    // cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true); 
    // gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN); 
    // TEST_ASSERT_MESSAGE(gpio == 1, "LED successfully turned on");
}

/**REMOVE AFTER CONFIRMING; THIS IS A TEST FROM THE REFERENCE IMPLEMENTATION */

void test_blinking(void)
{
    int count = 0;
    bool on = 0;
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, 0);
    for (int i = 0; i < 200; i += 1) {
        int curr_count = count;
        bool next_on = do_blink(on, &count);
        int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN);
        TEST_ASSERT_EQUAL_MESSAGE(gpio, on, "GPIO should be set to the state of 'on' variable.");
        TEST_ASSERT_EQUAL_MESSAGE(count, curr_count +1, "Always increment the count");
        if ((i+1) % 11) {
            TEST_ASSERT_NOT_EQUAL_MESSAGE(on, next_on, "Should toggle when count is not a multiple of 11.");
        } else {
            TEST_ASSERT_EQUAL_MESSAGE(on, next_on, "Should not toggle otherwise.");
        }
        on = next_on;
    }
}

void test_variable_assignment()
{
    int x = 1;
    TEST_ASSERT_TRUE_MESSAGE(x == 1,"Variable assignment failed.");
}

void test_multiplication(void)
{
    int x = 30;
    int y = 6;
    int z = x / y;
    TEST_ASSERT_TRUE_MESSAGE(z == 5, "Multiplication of two integers returned incorrect value.");
}

void blank_test(void) {
    printf("This is a test. If you see this message then the blank test has succeeded.\n");
}

int main (void)
{
    stdio_init_all();
    hard_assert(cyw43_arch_init() == PICO_OK);
    while(1) {
	sleep_ms(5000); // Give time for TTY to attach.
	printf("Start tests\n");
	UNITY_BEGIN();
	// RUN_TEST(test_change_case);
	RUN_TEST(test_blinking);
	UNITY_END();
    }
}