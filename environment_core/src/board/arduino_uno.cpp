#include "arduino_uno.h"
#include <avr/io.h>


const ArduinoUno::PinDefinition ArduinoUno::pin_map[1] = {
    {&DDRB, &PORTB, &PINB, 5 }
};

void ArduinoUno::pin_mode(uint8_t pin, bool output)
{
    auto& p = pin_map[pin];
    if (output)
        *p.ddr |= (1 << p.bit);
    else
        *p.ddr &= ~(1 << p.bit);
}

void ArduinoUno::digital_write(uint8_t pin, bool high)
{
    auto& p = pin_map[pin];
    if (high)
        *p.port |= (1 << p.bit);
    else
        *p.port &= ~(1 << p.bit);
}

bool ArduinoUno::digital_read(uint8_t pin)
{
    return false;
}