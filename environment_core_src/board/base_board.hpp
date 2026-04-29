#pragma once

#include <stdint.h>

class Board
{
public:
    enum class PinMode
    {
        OUTPUT,
        INPUT,
        INPUT_PULLUP
    };
    union OCRRegister
    {
        volatile uint8_t*  ocr8;
        volatile uint16_t* ocr16;
    };
    struct PinDefinition
    {
        volatile uint8_t* ddr {nullptr};
        volatile uint8_t* port {nullptr};
        volatile uint8_t* pin_reg {nullptr};
        uint8_t bit {0};

        // PWM
        volatile uint8_t* tccra {nullptr}; // If nullptr -> No PWM support
        volatile uint8_t* tccrb {nullptr};
        OCRRegister ocr;
        uint8_t com_mask {0};
        bool is_16bit {false};
    };
    Board() = default;
    virtual void init_pwm() = 0;
    virtual void pin_mode(uint8_t pin, PinMode pin_mode) = 0;
    virtual void digital_write(uint8_t pin, bool high) = 0;
    virtual bool digital_read(uint8_t pin) = 0;
    virtual void pwm_write(uint8_t pin, uint8_t value) = 0;
};