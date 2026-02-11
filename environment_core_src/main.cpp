
#include <util/delay.h>

#include "board/arduino_uno.h"
#include "output_modules/traffic_light.h"
#include "output_modules/led.h"

int main()
{
    ArduinoUno board;
    TrafficLight traffic_light(board, 8, 9, 10);

    Led build_in_led(board, 13);

    while (true)
    {
        traffic_light.turn_light_on(TrafficColor::GREEN, false);
        traffic_light.turn_light_on(TrafficColor::RED, true);
        _delay_ms(1500);
        traffic_light.turn_light_on(TrafficColor::RED, false);
        traffic_light.turn_light_on(TrafficColor::YELLOW, true);
        _delay_ms(1000);
        traffic_light.turn_light_on(TrafficColor::YELLOW, false);
        traffic_light.turn_light_on(TrafficColor::GREEN, true);
        _delay_ms(2000);
    }
    
    return 0;
}
