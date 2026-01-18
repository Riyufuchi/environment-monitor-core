//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-18
// Last edit  : 2026-01-18
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "traffic_light.h"

TrafficLight::TrafficLight(uint8_t pin_red, uint8_t pin_yellow, uint8_t pin_green)
{
	pins[0] = pin_red;
	pins[1] = pin_yellow;
	pins[2] = pin_green;
	// Set pins as output
	DDRD |= (1 << this->pins[0]);
	DDRD |= (1 << this->pins[1]);
	DDRD |= (1 << this->pins[2]);

	// Set pins low
	PORTD &= ~(1 << this->pins[0]);
	PORTD &= ~(1 << this->pins[1]);
	PORTD &= ~(1 << this->pins[2]);
}

void TrafficLight::turn_light(TRAFFIC_LIGHT light, bool on)
{
	if (on)
		PORTD |= (1 << pins[static_cast<uint8_t>(light)]);
	else
		PORTD &= ~(1 << pins[static_cast<uint8_t>(light)]);
}
