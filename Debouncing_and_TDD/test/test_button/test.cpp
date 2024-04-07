/**
 * @file main.cpp
 * @author Marcus Robertsson (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-05-29
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "unity.h"
#include "bsp.h"
#include "button.h"

static int pin = 34;

void setUp(void) {}

void tearDown(void) {}

void test_button_init(void)
{
    button_init(pin);

    TEST_ASSERT_TRUE(button_get_init());
}

void test_get_bad_testing_name_dev(void)
{

    uint8_t test_state = BUTTON_UNINITITIALIZED;

    bsp_set_buff(0, 0);
    button_update_state();
    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_UNINITITIALIZED, test_state);

    button_init(pin);
    bsp_set_buff(0, 0);
    for (size_t i = 0; i < 5; i++)
    {
        button_update_state();
    }

    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, test_state);

    bsp_set_buff(1, 1);
    for (size_t i = 0; i < 5; i++)
    {
        button_update_state();
    }

    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, test_state);

    bsp_set_buff(1, 0);
    for (size_t i = 0; i < 5; i++)
    {
        button_update_state();
    }
    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, test_state);

    bsp_set_buff(0, 0);
    for (size_t i = 0; i < 5; i++)
    {
        button_update_state();
    }
    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, test_state);

    bsp_set_buff(1, 0);
    for (size_t i = 0; i < 5; i++)
    {
        button_update_state();
    }
    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, test_state);

    button_set_state(BUTTON_PRESSED);

    bsp_set_buff(1, 1);
    for (size_t i = 0; i < 5; i++)
    {
        button_update_state();
    }
    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, test_state);

    button_set_state(BUTTON_RELEASED);

    bsp_set_buff(0, 0);
    for (size_t i = 0; i < 5; i++)
    {
        button_update_state();
    }
    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, test_state);
}

void test_get_bad_testing_name_dev_esp32(void)
{
    uint8_t test_state = BUTTON_UNINITITIALIZED;

    button_init(pin);
    bsp_set_pin_state(BSP_LOW);
    for (size_t i = 0; i < 5; i++)
    {
        button_update_state();
    }
    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_FALLING_EDGE, test_state);

    bsp_set_pin_state(BSP_HIGH);
    for (size_t i = 0; i < 5; i++)
    {
        button_update_state();
    }
    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, test_state);

    bsp_set_pin_state(BSP_LOW);
    for (size_t i = 0; i < 3; i++)
    {
        button_update_state();
    }
    bsp_set_pin_state(BSP_HIGH);
    button_update_state();
    button_update_state();
    test_state = button_get_state();
    TEST_ASSERT_EQUAL_UINT8(BUTTON_RISING_EDGE, test_state);
}

#ifdef DEVENV
int main(void)
{
#else
void loop()
{
}

void setup()
{

#endif
    UNITY_BEGIN();
#ifdef DEVENV

    RUN_TEST(test_get_bad_testing_name_dev);
#else

    RUN_TEST(test_get_bad_testing_name_dev_esp32);

#endif

    RUN_TEST(test_button_init);

#ifdef DEVENV
    return UNITY_END();
#else
    UNITY_END();
#endif
}