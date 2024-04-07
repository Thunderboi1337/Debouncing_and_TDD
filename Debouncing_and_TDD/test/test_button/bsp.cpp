#include "bsp.h"
#include "button.h"
#include <string.h>
// buffer or something simliar that send 1 or 0 to the read function

#ifndef DEVENV
#include <Arduino.h>
#endif

#define BUFF_SIZE 5

static uint8_t buff[BUFF_SIZE];
static size_t indx = 0;

static bool bsp_init = false;
static uint8_t pin_num = 0xFFU;
static uint8_t pin_mode = 0xFFU;
static uint8_t pin_state = 0xFFU;

void bsp_pin_mode(uint8_t x, uint8_t y)
{
    pin_num = x;
    pin_mode = y;
    bsp_init = true;
}

int bsp_digital_read(uint8_t x)
{
    // read from buffer or from something that sends one or zero.

    pin_num = x;
    int read;
#ifdef DEVENV

    if (indx < BUFF_SIZE)
    {
        read = buff[indx++];
    }
    indx = indx % BUFF_SIZE;
#else
    read = pin_state;

#endif

    return read;
}

// Helperfunctions

void bsp_set_buff(uint8_t numb, uint8_t disrupt)
{
    for (int i = 0; i < BUFF_SIZE; i++)
    {
        buff[i] = numb;
    }

    buff[BUFF_SIZE - 2] = disrupt;
}

uint8_t bsp_get_pin_num(void)
{
    return pin_num;
}

uint8_t bsp_get_pin_mode(void)
{
    return pin_mode;
}

uint8_t bsp_get_pin_state(void)
{
    return pin_state;
}
void bsp_set_pin_state(uint8_t state)
{
    pin_state = state;
}
void bsp_set_pin_mode(uint8_t mode)
{
    pin_mode = mode;
}
