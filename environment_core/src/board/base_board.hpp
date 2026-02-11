#pragma once

#include <stdint.h>

class Board
{
public:
    struct PinDefinition
    {
        volatile uint8_t* ddr {nullptr};
        volatile uint8_t* port {nullptr};
        volatile uint8_t* pin_reg {nullptr};
        uint8_t bit {0};
    };
    Board() = default;
   // virtual ~Board();
    virtual void pin_mode(uint8_t pin, bool output) = 0;
    virtual void digital_write(uint8_t pin, bool high) = 0;
    virtual bool digital_read(uint8_t pin) = 0;
};