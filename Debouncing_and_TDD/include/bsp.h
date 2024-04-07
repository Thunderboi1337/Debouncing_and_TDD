#ifndef BSP_H
#define BSP_H

#include <Arduino.h>

#define BSP_LOW LOW
#define BSP_HIGH HIGH
#define BSP_INPUT_PULLUP INPUT_PULLUP

static inline void bsp_pin_mode(uint8_t x, uint8_t y) { pinMode(x, y); }

static inline int bsp_digital_read(uint8_t x) { return digitalRead(x); }

#endif /* BSP_H */

// PULLUP RESISTOR ADD