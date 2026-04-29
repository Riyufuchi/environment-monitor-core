#include "arduino_uno.h"
#include <avr/io.h>

const ArduinoUno::PinDefinition ArduinoUno::pin_map[14] = {
    // D0
    {&DDRD, &PORTD, &PIND, 0, nullptr, nullptr, {.ocr8 = nullptr}, 0, false},
    // D1
    {&DDRD, &PORTD, &PIND, 1, nullptr, nullptr, {.ocr8 = nullptr}, 0, false},
    // D2
    {&DDRD, &PORTD, &PIND, 2, nullptr, nullptr, {.ocr8 = nullptr}, 0, false},
    // D3 (PWM - Timer2 OC2B)
    {&DDRD, &PORTD, &PIND, 3, &TCCR2A, &TCCR2B, {.ocr8 = &OCR2B}, (1 << COM2B1), false},
    // D4
    {&DDRD, &PORTD, &PIND, 4, nullptr, nullptr, {.ocr8 = nullptr}, 0, false},
    // D5 (PWM - Timer0 OC0B)
    {&DDRD, &PORTD, &PIND, 5, &TCCR0A, &TCCR0B, {.ocr8 = &OCR0B}, (1 << COM0B1), false},
    // D6 (PWM - Timer0 OC0A)
    {&DDRD, &PORTD, &PIND, 6, &TCCR0A, &TCCR0B, {.ocr8 = &OCR0A}, (1 << COM0A1), false},
    // D7
    {&DDRD, &PORTD, &PIND, 7, nullptr, nullptr, {.ocr8 = nullptr}, 0, false},
    // D8
    {&DDRB, &PORTB, &PINB, 0, nullptr, nullptr, {.ocr8 = nullptr}, 0, false},
    // D9 (PWM - Timer1 OC1A, 16-bit)
    {&DDRB, &PORTB, &PINB, 1, &TCCR1A, &TCCR1B, {.ocr16 = &OCR1A}, (1 << COM1A1), true},
    // D10 (PWM - Timer1 OC1B, 16-bit)
    {&DDRB, &PORTB, &PINB, 2, &TCCR1A, &TCCR1B, {.ocr16 = &OCR1B}, (1 << COM1B1), true},
    // D11 (PWM - Timer2 OC2A)
    {&DDRB, &PORTB, &PINB, 3, &TCCR2A, &TCCR2B, {.ocr8 = &OCR2A}, (1 << COM2A1), false},
    // D12
    {&DDRB, &PORTB, &PINB, 4, nullptr, nullptr, {.ocr8 = nullptr}, 0, false},
    // D13
    {&DDRB, &PORTB, &PINB, 5, nullptr, nullptr, {.ocr8 = nullptr}, 0, false}
};

void ArduinoUno::init_pwm()
{
    // Timer0 (pins 5,6)
    TCCR0A = (1 << WGM00) | (1 << WGM01);
    TCCR0B = (1 << CS01); // prescaler 8

    // Timer1 is for precise timing in sensor reads
    // Timer1 (pins 9,10)
    //TCCR1A = (1 << WGM10);
    //TCCR1B = (1 << WGM12) | (1 << CS11);

    // Timer2 (pins 3,11)
    TCCR2A = (1 << WGM20) | (1 << WGM21);
    TCCR2B = (1 << CS21);
}

void ArduinoUno::pin_mode(uint8_t pin, PinMode pin_mode)
{
    auto& p = pin_map[pin];
    
    switch (pin_mode)
    {
        case PinMode::OUTPUT:
            *p.ddr |= (1 << p.bit);
        break;
        case PinMode::INPUT:
            *p.ddr &= ~(1 << p.bit);
            *p.port &= ~(1 << p.bit); // Without pull-up
        break;
        case PinMode::INPUT_PULLUP:
            *p.ddr &= ~(1 << p.bit);
            *p.port |= (1 << p.bit); // With pull-up
        break;
    }
}

void ArduinoUno::digital_write(uint8_t pin, bool high)
{
    auto& p = pin_map[pin];
    if (high)
        *p.port |= (1 << p.bit);
    else
        *p.port &= ~(1 << p.bit);
}

bool ArduinoUno::digital_read(uint8_t pin)
{
    auto& p = pin_map[pin];
    return (*p.pin_reg & (1 << p.bit)) != 0;
}

void ArduinoUno::pwm_write(uint8_t pin, uint8_t value)
{
    auto& p = pin_map[pin];

    if (!p.tccra)
        return; // no PWM

    // set as output
    *p.ddr |= (1 << p.bit);

    // enable non-inverting PWM
    *p.tccra |= p.com_mask;

    if (p.is_16bit)
    {
        // scale 8-bit (0–255) to 16-bit range
        *p.ocr.ocr16 = static_cast<uint16_t>(value) << 2; 
        // (simple scaling; can be improved depending on TOP)
    }
    else
    {
        *p.ocr.ocr8 = value;
    }
}