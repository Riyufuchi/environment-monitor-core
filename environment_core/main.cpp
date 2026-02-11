extern "C"
{
#include "src/sos/sos.h"
}

//#include "src/output_modules/traffic_light.h"
#include "src/board/arduino_uno.h"

int main()
{
    ArduinoUno board;
    board.pin_mode(0, false);
    _delay_ms(250);
    while (true)
    {
        board.pin_mode(0, true);
        _delay_ms(500);
        board.pin_mode(0, false);
        _delay_ms(500);
    }
    return 0;
  /*sos_init();
  while (1)
    sos_task();
  return 0;*/
}
