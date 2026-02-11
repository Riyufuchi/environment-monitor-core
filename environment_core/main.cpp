extern "C"
{
#include "src/sos/sos.h"
}

#include "src/board/arduino_uno.h"
#include "src/output_modules/traffic_light.h"

int main()
{
    ArduinoUno board;
    TrafficLight traffic_light(board, 8, 9, 10);

    board.pin_mode(13, true);
    board.digital_write(13, false);

    while (true)
    {
        traffic_light.turn_light(TrafficColor::GREEN, false);
        traffic_light.turn_light(TrafficColor::RED, true);
        _delay_ms(1500);
        traffic_light.turn_light(TrafficColor::RED, false);
        traffic_light.turn_light(TrafficColor::YELLOW, true);
        _delay_ms(1000);
        traffic_light.turn_light(TrafficColor::YELLOW, false);
        traffic_light.turn_light(TrafficColor::GREEN, true);
        _delay_ms(2000);
    }
    
    return 0;
}
