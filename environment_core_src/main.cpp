
#include <util/delay.h>

#include "board/arduino_uno.h"
#include "board/base_board.hpp"
#include "output_modules/led.h"

int main()
{
    ArduinoUno board;

    Led build_in_led(board, 13);

    board.pin_mode(3, Board::PinMode::OUTPUT);
    board.digital_write(3, false);
    board.pin_mode(7, Board::PinMode::INPUT_PULLUP);

    while (true)
    {
        board.digital_write(3, false);
        if (board.digital_read(7))
            build_in_led.turn_on(true);
        else
            build_in_led.turn_on(false);

        _delay_ms(1000);
        
        board.digital_write(3, true);
        if (board.digital_read(7))
            build_in_led.turn_on(true);
        else
            build_in_led.turn_on(false);

        _delay_ms(1000);
    }
    
    return 0;
}
