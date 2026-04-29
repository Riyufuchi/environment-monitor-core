//==============================================================================
// Author     : riyufuchi
// Created on : 2026-04-29
// Last edit  : 2026-04-29
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef SERIAL_PORT_HPP
#define SERIAL_PORT_HPP

#include <string>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <cstring>
#include <iostream>
#include <cstdint>

class SerialPort
{
public:
	bool open_port(const std::string& device, int baud)
	{
		fd = open(device.c_str(), O_RDWR | O_NOCTTY | O_SYNC);
		if (fd < 0)
		{
			perror("open");
			return false;
		}

		termios tty{};
		if (tcgetattr(fd, &tty) != 0)
		{
			perror("tcgetattr");
			return false;
		}

		cfmakeraw(&tty);

		speed_t speed = baud_rate(baud);
		cfsetispeed(&tty, speed);
		cfsetospeed(&tty, speed);

		tty.c_cflag |= (CLOCAL | CREAD);
		tty.c_cflag &= ~PARENB;
		tty.c_cflag &= ~CSTOPB;
		tty.c_cflag &= ~CSIZE;
		tty.c_cflag |= CS8;

		tty.c_cc[VMIN]  = 0;
		tty.c_cc[VTIME] = 10; // 1s timeout (0.1s units)

		if (tcsetattr(fd, TCSANOW, &tty) != 0)
		{
			perror("tcsetattr");
			return false;
		}

		return true;
	}

	int read_data(uint8_t* buffer, size_t size)
	{
		return ::read(fd, buffer, size);
	}

	void close_port()
	{
		if (fd >= 0)
			::close(fd);
	}

private:
	int fd = -1;

	speed_t baud_rate(int baud)
	{
		switch (baud) {
			case 9600: return B9600;
			case 19200: return B19200;
			case 38400: return B38400;
			case 57600: return B57600;
			case 115200: return B115200;
			default: return B9600;
		}
	}
};

#endif // SERIAL_PORT_HPP
