#include "blink.h"

#include <avr/io.h>     // AVR register definitions (DDRx, PORTx, PINx, etc.)
#include <util/delay.h> // provides _delay_ms() and _delay_us()

// Initialize the LED pin
void blink_init(void)
{
    // Arduino Uno digital pin 13 is AVR Port B, bit 5 (PB5).
    // DDRx (Data Direction Register) controls INPUT/OUTPUT mode:
    //   0 = input, 1 = output
    // Here we set PB5 to 1 → configure as OUTPUT.
    DDRB |= (1 << PB5);  
    // This is equivalent to: pinMode(13, OUTPUT);
}

// Blink task toggles the LED
void blink_task(void)
{
    // PORTx controls the actual HIGH/LOW state of an output pin.
    // XOR with (1 << PB5) flips the bit each call:
    //   - if LED was ON → turn it OFF
    //   - if LED was OFF → turn it ON
    // this is toggle, it stays on either HIGH or LOW
    PORTB ^= (1 << PB5);

    // Simple blocking delay: wait 500 milliseconds
    _delay_ms(500);
}

_Bool isOn(void)
{
  return 1;
}

