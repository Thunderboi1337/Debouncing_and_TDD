#include "bsp.h"
#include "button.h"
#include <stdbool.h>
#include <cstdio>

#define SAMPLES (5U)
static bool initialized = false;
uint8_t state = BUTTON_UNINITITIALIZED;
static uint8_t pin_num = 0xFFU;

void button_init(uint8_t pin)
{
    pin_num = pin;
    initialized = true;
    state = BUTTON_RELEASED;
    bsp_pin_mode(pin, BSP_INPUT_PULLUP);
}

void button_update_state(void)
{

    if (state != BUTTON_UNINITITIALIZED)
    {
        uint8_t read;
        static int counter = 0;

        read = bsp_digital_read(pin_num);

        if (state == BUTTON_FALLING_EDGE || state == BUTTON_PRESSED)
        {

            if (read == BSP_HIGH)
            {
                counter++;
            }
            else
            {
                counter = 0;
            }
        }
        if (state == BUTTON_RISING_EDGE || state == BUTTON_RELEASED)
        {

            if (read == BSP_LOW)
            {
                counter++;
            }
            else
            {
                counter = 0;
            }
        }
        if (counter == 5)
        {
            if (state == BUTTON_PRESSED)
            {
                state = BUTTON_FALLING_EDGE;
            }
            if (state == BUTTON_RELEASED)
            {
                state = BUTTON_RISING_EDGE;
            }

            state = state == BUTTON_RISING_EDGE ? BUTTON_FALLING_EDGE : BUTTON_RISING_EDGE;

            counter = 0;
        }
    }
}

uint8_t button_get_state(void)
{
    return state;
}

// Helpter functions
// pinstate
// counter functions if

uint8_t button_get_init(void)
{
    return initialized;
}
void button_set_state(uint8_t set_state)
{
    state = set_state;
}