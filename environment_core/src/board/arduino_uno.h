#pragma once

#include "base_board.hpp"

class ArduinoUno final : public Board
{
public:
    static const PinDefinition pin_map[1];
    virtual void pin_mode(uint8_t pin, bool output) override;
    virtual void digital_write(uint8_t pin, bool high) override;
    virtual bool digital_read(uint8_t pin) override;
};