#include <stdio.h>
#include <pico/stdlib.h>
#include <stdint.h>
#include <unity.h>
#include "unity_config.h"
#include "pico/cyw43_arch.h"

void setUp(void) {}

void tearDown(void) {}

void test_LED(void) {
    printf("Starting LED test\n");
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, false); 
    printf("Attempting to force LED off\n");
    int gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN); 
    TEST_ASSERT_MESSAGE(gpio == 0, "LED successfully turned off");
    cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, true); 
    gpio = cyw43_arch_gpio_get(CYW43_WL_GPIO_LED_PIN); 
    TEST_ASSERT_MESSAGE(gpio == 1, "LED successfully turned on");
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
    while (1) {
        sleep_ms(5000); // Give time for TTY to attach.
        printf("Start tests\n");
        UNITY_BEGIN();
        RUN_TEST(test_variable_assignment);
        RUN_TEST(test_multiplication);
        fflush(stdout);
        printf("End Tests\n");
        RUN_TEST(blank_test);
        // RUN_TEST(test_LED);
        // sleep_ms(5000);
        UNITY_END();
    }
}
