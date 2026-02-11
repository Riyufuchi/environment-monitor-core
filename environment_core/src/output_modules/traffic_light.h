//==============================================================================
// Author     : riyufuchi
// Created on : 2026-01-18
// Last edit  : 2026-02-10
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "../board/base_board.hpp"

enum class TrafficColor
{
	RED,
	YELLOW,
	GREEN
};

class TrafficLight
{
private:
    Board& board_pin_map;
	uint8_t pins[3];
public:
	TrafficLight(Board& board_pin_map, uint8_t pin_red, uint8_t pin_yellow, uint8_t pin_green);
	void turn_light(TrafficColor color, bool on);
};

#endif // TRAFFIC_LIGHT_H
