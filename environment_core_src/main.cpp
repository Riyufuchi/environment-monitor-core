
#include <util/delay.h>
#include <stdio.h>

#include "board/arduino_uno.h"
#include "board/base_board.hpp"

#include "output_modules/led.h"

#include "input_modules/Dht22.h"

#include "protocols/uart.hpp"

#include "tools/Timer.h"

int main()
{
    ArduinoUno board;

    Timer::init_millis_timer1();

    Led build_in_led(board, 13);

    board.pin_mode(3, Board::PinMode::OUTPUT);
    board.digital_write(3, false);
    board.pin_mode(7, Board::PinMode::INPUT_PULLUP);

    UART::init(UART::BaudRate::BR_9600);

    Dht22 dht22(board, 7);
    
    char text[32];

    uint32_t now, last_read = 6000;
    bool was_read_ok = false;

    while (true)
    {
        now = Timer::millis();

        if (now - last_read >= 2000 || !was_read_ok)
        {
            last_read = now;
            was_read_ok = dht22.read_data();
            build_in_led.turn_on(!dht22.is_valid());

            snprintf(text, sizeof(text),
                "%d;%d;%d;%d\n",
                dht22.is_valid(),
                dht22.get_tempeture_x10(),
                dht22.get_humidity_x10(),
                dht22.get_error_code());
        

            UART::send_string(text);
        }


       // _delay_ms(5000);
    }
    
    return 0;
}
