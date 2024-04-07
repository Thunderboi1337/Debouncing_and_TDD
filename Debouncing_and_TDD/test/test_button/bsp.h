#ifndef BSP_H
#define BSP_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define BSP_LOW 0
#define BSP_HIGH 1
#define BSP_INPUT_PULLUP 0x05

void bsp_pin_mode(uint8_t x, uint8_t y);

int bsp_digital_read(uint8_t x);

// HEllpers

void bsp_set_buff(uint8_t numb, uint8_t disrupt);

uint8_t bsp_get_pin_num(void);

uint8_t bsp_get_pin_mode(void);

uint8_t bsp_get_pin_state(void);

void bsp_set_pin_state(uint8_t state);

void bsp_set_pin_mode(uint8_t mode);

#endif
