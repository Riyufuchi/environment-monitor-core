//==============================================================================
// Author     : riyufuchi
// Created on : 2026-05-01
// Last edit  : 2026-05-01
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../external/httplib.h"

#include "../ports/serial_port.hpp"

#include "consolelib/tools/console_tools.h"

namespace env_core
{

class Controller
{
private:
	httplib::Server server_http;
	SerialPort port;
	std::mutex data_mutex;
	std::string latest_value;
	std::jthread server_thread;
	std::jthread serial_port_thread;
	struct
	{
		int valid_data {0};
		int invalid_data {0};
	} stats;
	struct
	{
		bool success {false};
		double tempeture {0};
		double humidity {0};
		int error_code {-1};
	} recieved_data;
	void init_server();
	void init_port();
	void decode_data_asyc();
	void serial_worker(std::stop_token st, SerialPort& port, std::string& latest_value, std::mutex& data_mutex);
public:
	Controller();
	~Controller();
	void print_header();
	void init();
	double calc_percentage_success();
};

}

#endif // CONTROLLER_H
