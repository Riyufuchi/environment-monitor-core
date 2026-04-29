#pragma once
#include <avr/io.h>

class UART
{
public:
    enum class BaudRate : uint32_t
    {
        BR_9600 = 9600,
        BR_19200 = 19200,
        BR_38400 = 38400,
        BR_57600 = 57600,
        BR_115200 = 115200
    };

    static void init(BaudRate baud)
    {
        uint16_t ubrr = calculate_ubrr(static_cast<uint32_t>(baud));

        UBRR0H = (ubrr >> 8);
        UBRR0L = ubrr;

        // Enable transmitter
        UCSR0B = (1 << TXEN0);

        // 8 data bits, 1 stop bit
        UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    }

    static void send_byte(uint8_t data)
    {
        // Wait for empty transmit buffer
        while (!(UCSR0A & (1 << UDRE0)));

        // Put data into buffer
        UDR0 = data;
    }

    static void send_string(const char* str)
    {
        while (*str) {
            send_byte(*str++);
        }
    }

private:
    static uint16_t calculate_ubrr(uint32_t baud)
    {
       // constexpr uint32_t F_CPU = 16000000UL;
        return (F_CPU / (16UL * baud)) - 1;
    }
};