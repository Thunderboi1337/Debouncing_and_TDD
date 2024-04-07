#include "bsp.h"
#include "button.h"

void setup()
{
    Serial.begin(9600);

    button_init(34);

    constexpr uint16_t DIVIDER{80};
    constexpr uint32_t INTERVAL{2000};

    hw_timer_t *timer{timerBegin(0, DIVIDER, true)};
    timerAttachInterrupt(timer, &button_update_state, true);

    timerAlarmWrite(timer, INTERVAL, true);

    timerAlarmEnable(timer);
}

void loop()
{
    uint8_t state = button_get_state();

    if (state == BUTTON_RISING_EDGE)
    {
        Serial.println("Rising edge");
        state = BUTTON_RELEASED;
    }
    if (state == BUTTON_FALLING_EDGE)
    {
        Serial.println("Falling edge");
        state = BUTTON_PRESSED;
    }
}
