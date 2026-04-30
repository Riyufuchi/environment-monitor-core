#include "Timer.h"

// Definice statické proměnné (musí být mimo třídu, obvykle v .cpp souboru)
unsigned long Timer::timer_millis = 0;
volatile uint32_t Timer::timer1_overflow = 0;

// ISR musí být mimo třídu
ISR(TIMER1_COMPA_vect) {
    Timer::tick();
}

ISR(TIMER1_OVF_vect)
{
    Timer::timer1_overflow++;
}

void Timer::init_millis_timer1(void)
{
       TCCR1B |= (1 << WGM12);  // CTC režim
       TCCR1B |= (1 << CS11);   // Prescaler 8
       OCR1A = 1999;            // 1ms při 16MHz
       TIMSK1 |= (1 << OCIE1A); // Povolení přerušení
       TIMSK1 |= (1 << TOIE1);
       sei();
}

unsigned long Timer::millis(void)
 {
    unsigned long m;
    uint8_t oldSREG = SREG;
    cli();
    m = timer_millis;
    SREG = oldSREG;
    return m;
}

unsigned long Timer::micros()
{
    uint8_t oldSREG = SREG;
    cli();

    uint16_t t = TCNT1;
    uint32_t overflows = timer1_overflow;

    // if overflow happened but not yet synced
    if ((TIFR1 & (1 << TOV1)) && t < 65535)
        overflows++;

    SREG = oldSREG;

    // each tick = 0.5 µs (prescaler 8 at 16 MHz)
    return ((overflows << 16) + t) * 0.5;
}

    // Metoda, kterou zavolá ISR (musí být public nebo přítel)
 void Timer::tick() {
        timer_millis++;
    }