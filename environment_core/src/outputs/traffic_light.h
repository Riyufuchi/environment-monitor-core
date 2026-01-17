#ifndef _TRAFFIC_LIGHT_H_
#define _TRAFFIC_LIGHT_H_

#include <avr/io.h>     // AVR registers: DDRx, PORTx, PINx
#include <util/delay.h> // _delay_ms()

// ---------------------------
// Public API
// ---------------------------
typedef struct
{
  uint8_t pin_red;
  uint8_t pin_yellow;
  uint8_t pin_green;
} tTrafficLight;

void init_trafficLight(tTrafficLight* module);
void turn_light(uint8_t pin, _Bool on);

// ---------------------------
// Internal helpers
// ---------------------------

#endif
