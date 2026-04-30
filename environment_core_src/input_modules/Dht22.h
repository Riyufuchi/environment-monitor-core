#pragma once

#include "../board/base_board.hpp"
class Dht22
{
private:
    Board& board_pin_map;
	uint8_t data_pin;
    uint8_t recieved_data[5]; // 40-bit -> 16 bit temp, 16 bit humidity and 8 bit checksum
    uint8_t error_code;
    struct data
    {
        int16_t temp_x10 {0};
        int16_t humidity_x10 {0};
        double temp {0};
        double humidity {0};
        bool is_valid {false};
    } parsed_data;
    bool hand_shake();
    bool read_sequence();
    bool parse_data();
public:
    Dht22(Board& board_pin_map, uint8_t data_pin);
    bool read_data();
    int16_t get_tempeture_x10() const;
    int16_t get_humidity_x10() const;
    double get_tempeture() const;
    double get_humidity() const;
    bool is_valid() const;
    uint8_t get_error_code() const;
};