//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-18
// Last edit  : 2026-02-10
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <avr/io.h>     // AVR registers: DDRx, PORTx, PINx
#include <util/delay.h> // _delay_ms()

enum class TrafficColor
{
	RED,
	YELLOW,
	GREEN
};

class TrafficLight
{
private:
	uint8_t pins[3];
public:
	TrafficLight(uint8_t pin_red, uint8_t pin_yellow, uint8_t pin_green);
	void turn_light(TrafficColor color, bool on);
};

#endif // TRAFFIC_LIGHT_H
