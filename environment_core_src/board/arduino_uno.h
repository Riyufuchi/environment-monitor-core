#pragma once

#include "base_board.hpp"

class ArduinoUno final : public Board
{
public:
    static const PinDefinition pin_map[14];
    virtual void init_pwm() override;
    virtual void pin_mode(uint8_t pin, PinMode pin_mode) override;
    virtual void digital_write(uint8_t pin, bool high) override;
    virtual bool digital_read(uint8_t pin) override;
    virtual void pwm_write(uint8_t pin, uint8_t value) override;

};