
#include <util/delay.h>

#include "board/arduino_uno.h"
#include "board/base_board.hpp"
#include "output_modules/led.h"

#include "protocols/uart.hpp"

int main()
{
    ArduinoUno board;

    Led build_in_led(board, 13);

    board.pin_mode(3, Board::PinMode::OUTPUT);
    board.digital_write(3, false);
    board.pin_mode(7, Board::PinMode::INPUT_PULLUP);

    UART::init(UART::BaudRate::BR_9600);

    char temp = 'a';
    char humi = 'A';
    
    char text[5];
    text[0] = temp;
    text[1] = ';';
    text[2] = humi;
    text[3] = '\n';
    text[4] = '\0';

    while (true)
    {
        if (temp == 'z')
            temp = 'a';
        if (humi == 'Z')
            humi = 'A';

        text[0] = temp;
        text[2] = humi;

        UART::send_string(text);

        temp++;
        humi++;

        _delay_ms(1000);
    }
    
    return 0;
}
