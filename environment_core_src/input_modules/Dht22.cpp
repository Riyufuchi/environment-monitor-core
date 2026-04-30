#include "Dht22.h"

#include <util/delay.h>
#include "../tools/Timer.h"

Dht22::Dht22(Board& board_pin_map, uint8_t data_pin) : board_pin_map(board_pin_map), data_pin(data_pin)
{
    board_pin_map.pin_mode(data_pin, Board::PinMode::INPUT_PULLUP);
    this->error_code = 255;
}

int16_t Dht22::get_tempeture_x10() const
{
    return parsed_data.temp_x10;
}
    
int16_t Dht22::get_humidity_x10() const
{
    return parsed_data.humidity_x10;
}

double Dht22::get_tempeture() const
{
    return parsed_data.temp;
}

double Dht22::get_humidity() const
{
    return parsed_data.humidity;
}
bool Dht22::is_valid() const
{
    return parsed_data.is_valid;
}

uint8_t Dht22::get_error_code() const
{
    return error_code;
}

/*bool Dht22::hand_shake()
{
    board_pin_map.pin_mode(data_pin, Board::PinMode::OUTPUT);
    board_pin_map.digital_write(data_pin, false);
    //_delay_ms(2);
    board_pin_map.pin_mode(data_pin, Board::PinMode::INPUT_PULLUP);

    // Wait for DHT22 acknowledgment
    // 1. step wait for LOW
    uint32_t start = Timer::millis();
    while ((PIND & (1 << 7)) != 0)
    {
        if (Timer::millis() - start > 10)
        {
            error_code = 00;
            return false;
        }
    }
    // 2. Step wait for HIGHT
    while (!(PIND & (1 << 7)) != 0) // Wait for DHT22 acknowledgment 
    {
        if (Timer::millis() - start > 5)
        {
            error_code = 1;
            return false;
        }
    }
    // 3. step wait for final LOW
    while ((PIND & (1 << 7)) != 0)
    {
        if (Timer::millis() - start > 5)
        {
            error_code = 2;
            return false;
        }
    }

    return true;
}*/

bool Dht22::hand_shake()
{
    board_pin_map.pin_mode(data_pin, Board::PinMode::OUTPUT);
    board_pin_map.digital_write(data_pin, false);
    _delay_ms(1);
    board_pin_map.pin_mode(data_pin, Board::PinMode::INPUT_PULLUP);

    // Wait for DHT22 acknowledgment
    // 1. step wait for LOW
    uint32_t timeout = 10000;
    while (board_pin_map.digital_read(data_pin))
    {
        if (--timeout == 0)
        {
            error_code = 00;
            return false;
        }
    }
    // 2. Step wait for HIGHT
    timeout = 10000;
    while (!board_pin_map.digital_read(data_pin)) // Wait for DHT22 acknowledgment 
    {
        if (--timeout == 0)
        {
            error_code = 01;
            return false;
        }
    }
    // 3. step wait for final LOW
    timeout = 10000;
    while (board_pin_map.digital_read(data_pin))
    {
        if (--timeout == 0)
        {
            error_code = 02;
            return false;
        }
    }

    return true;
}

bool Dht22::read_sequence()
{
    uint8_t byte_index, bit_index;
    uint32_t timeout = 10000;

    uint32_t start, end;
    cli();
    for (int i = 0; i < 40; i++)
    {
        timeout = 10000;

        // 1. wait for LOW (sync start of bit)
        while (((PIND & (1 << 7)) != 0))
        {
            /*if (--timeout == 0)
            {
                error_code = 10;
                return false;
            }*/
        }

        // 2. wait for HIGH (bit begins)
        timeout = 10000;
        while (!((PIND & (1 << 7)) != 0))
        {
            /*if (--timeout == 0)
            {
                error_code = 11;
                return false;
            }*/
        }

        // 3. measure HIGH duration
        start = Timer::micros();
        while ((PIND & (1 << 7)) != 0)
        {
           /* if (Timer::micros() - start > 200)
            {
                error_code = 12;
                return false; // safety cap
            }*/
        }
        end = Timer::micros();

        byte_index = i / 8;
        bit_index  = 7 - (i % 8); // 7 because DHT22 sends MSB first

        // 4. interpret bit
        if (end - start >= 55)
        {
            recieved_data[byte_index] |= (1 << bit_index);
        }
        /*
        array is full of zeros already
        else
        {
            recieved_data[byte_index] &= ~(1 << bit_index);
        }*/
    }
    sei();

    return true;
}

bool Dht22::parse_data()
{
    uint16_t sum = recieved_data[0] + recieved_data[1] + recieved_data[2] + recieved_data[3];
    bool is_ok = true;

    if ((uint8_t)sum != recieved_data[4])
    {
        error_code = 20;
        is_ok = false;
    }

    uint16_t humidity = (recieved_data[0] << 8) | recieved_data[1];
    uint16_t temperature = (recieved_data[2] << 8) | recieved_data[3];

    bool negative = temperature & 0x8000;
    temperature &= 0x7FFF;

    parsed_data.temp_x10 = temperature;
    parsed_data.temp = temperature / 10.0f;
    if (negative)
    {
        parsed_data.temp = -parsed_data.temp;
        parsed_data.temp_x10 = -parsed_data.temp_x10;
    }

    parsed_data.humidity_x10 = humidity;
    parsed_data.humidity = humidity / 10.0f;

    return is_ok;
}

// TODO: Improve timeout to real time not tied directly to CPU spped
bool Dht22::read_data()
{
    // Clean previsous data
    for (int i = 0; i < 5; i++)
        recieved_data[i] = 0;
     parsed_data.is_valid = false;

    if (hand_shake() && read_sequence())
        parsed_data.is_valid = parse_data();

    return parsed_data.is_valid;
}