#pragma once

#include <avr/io.h>
#include <avr/interrupt.h>

class Timer
{
public:
    static unsigned long timer_millis;
    static volatile uint32_t timer1_overflow;

    static void init_millis_timer1(void);

    static unsigned long micros();
    static unsigned long millis(void);

    // Metoda, kterou zavolá ISR (musí být public nebo přítel)
    static void tick();
};



