//==============================================================================
// Author     : riyufuchi
// Created on : 2026-02-11
// Last edit  : 2026-02-11
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef LED_H
#define LED_H

#include "../board/base_board.hpp"

class Led
{
private:
    Board& board_pin_map;
	uint8_t pin;
public:
	Led(Board& board_pin_map, uint8_t pin);
	void turn_on(bool turn_on);
};

#endif
