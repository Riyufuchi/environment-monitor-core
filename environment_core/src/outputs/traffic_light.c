#include "traffic_light.h"

void init_trafficLight(tTrafficLight* module)
{
    // Set pins as output
    DDRD |= (1 << module->pin_red);
    DDRD |= (1 << module->pin_yellow);
    DDRD |= (1 << module->pin_green);
    
    // Set pins low
    PORTD &= ~(1 << module->pin_red);
    PORTD &= ~(1 << module->pin_yellow);
    PORTD &= ~(1 << module->pin_green);
}

void turn_light(uint8_t pin, _Bool on)
{
	if (on)
		PORTD |= (1 << pin);
	else
		PORTD &= ~(1 << pin);
}

