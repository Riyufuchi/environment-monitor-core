//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-18
// Last edit  : 2026-02-11
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "traffic_light.h"

TrafficLight::TrafficLight(Board& board_pin_map, uint8_t pin_red, uint8_t pin_yellow, uint8_t pin_green) : board_pin_map(board_pin_map)
{
	pins[0] = pin_red;
	pins[1] = pin_yellow;
	pins[2] = pin_green;

    for (int i = 0; i < 3; i++)
    {
        board_pin_map.pin_mode(this->pins[i], Board::PinMode::OUTPUT); // Set pins as output
        board_pin_map.digital_write(this->pins[i], false); // Set pins low
    }
}

void TrafficLight::turn_light_on(TrafficColor color, bool turn_on)
{
    board_pin_map.digital_write(pins[static_cast<uint8_t>(color)], turn_on);
}
