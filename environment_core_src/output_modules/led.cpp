//==============================================================================
// Author     : riyufuchi
// Created on : 2026-02-11
// Last edit  : 2026-02-11
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "led.h"

Led::Led(Board& board_pin_map, uint8_t pin) : board_pin_map(board_pin_map), pin(pin)
{
    board_pin_map.pin_mode(pin, Board::PinMode::OUTPUT);
    board_pin_map.digital_write(pin, false);
}

void Led::turn_on(bool turn_on)
{
    board_pin_map.digital_write(pin, turn_on);
}
