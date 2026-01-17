#include "sos.h"

// Initialize LED pin as output and flash twice for indication
void sos_init(void)
{
    DDRB |= (1 << LED_BUILTIN_PIN);  // Set pin as output
    // Initial flash sequence
    PORTB |= (1 << LED_BUILTIN_PIN);   // LED ON
    _delay_ms(INIT_DELAY);
    PORTB &= ~(1 << LED_BUILTIN_PIN);  // LED OFF
    _delay_ms(INIT_DELAY);
}

static inline void sos_blink3x_long()
{
  for (uint8_t i = 0; i < 3; i++) 
  {
    PORTB |= (1 << LED_BUILTIN_PIN);
    _delay_ms(LONG_DELAY);
    PORTB &= ~(1 << LED_BUILTIN_PIN);
    _delay_ms(LONG_DELAY);

  }
}

static inline void sos_blink3x_short()
{
  for (uint8_t i = 0; i < 3; i++) 
  {
    PORTB |= (1 << LED_BUILTIN_PIN);
    _delay_ms(SHORT_DELAY);
    PORTB &= ~(1 << LED_BUILTIN_PIN);
    _delay_ms(SHORT_DELAY);

  }
}

// SOS pattern: ··· ––– ···
void sos_task(void)
{
    PORTB &= ~(1 << LED_BUILTIN_PIN);
    _delay_ms(INIT_DELAY);

    sos_blink3x_short();
    _delay_ms(GAP_DELAY);
    sos_blink3x_long();
    _delay_ms(GAP_DELAY);
    sos_blink3x_short();
}


