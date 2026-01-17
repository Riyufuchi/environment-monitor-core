#ifndef _SOS_H_
#define _SOS_H_

#include <avr/io.h>     // AVR registers: DDRx, PORTx, PINx
#include <util/delay.h> // _delay_ms()

// ---------------------------
// Configurable parameters
// ---------------------------
#define LED_BUILTIN_PIN PB5  // Arduino Uno: pin 13
#define INIT_DELAY     2000  // ms
#define SHORT_DELAY     250  // ms (dot)
#define LONG_DELAY      500  // ms (dash)
#define GAP_DELAY       200  // ms gap between letters

// ---------------------------
// Public API
// ---------------------------
void sos_init(void);
void sos_task(void);

// ---------------------------
// Internal helpers
// ---------------------------
// static inline ensures the compiler can inline them
// and they are private to each compilation unit
static inline void sos_blink_short(void); // Short blink: · (dot)
static inline void sos_blink_long(void);  // Long blink: – (dash)

#endif
