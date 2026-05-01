//==============================================================================
// Author     : riyufuchi
// Created on : 2026-05-01
// Last edit  : 2026-05-01
// Copyright  : Copyright (c) 2026, riyufuchi
//==============================================================================
#include "controller.h"


env_core::Controller::Controller()
{

}

env_core::Controller::~Controller()
{
	serial_port_thread.request_stop();
	server_thread.request_stop();
	server_http.stop();
}

void
env_core::Controller::print_header()
{
	consolelib::console_tools::header("\nWeb service Ardo v1.0 - beta\n");
}

void env_core::Controller::init()
{
	init_server();
	init_port();
	consolelib::console_tools::wait_for_enter();
}

void env_core::Controller::serial_worker(std::stop_token st, SerialPort& port, std::string& latest_value, std::mutex& data_mutex)
{
	if (!port.open_port("/dev/ttyACM0", 9600))
	{
		std::lock_guard<std::mutex> lock(data_mutex);
		latest_value = "No device connected";
		return;
	}

	static uint8_t tmp[128];
	static std::string buffer;

	static int n, i;
	static char c;

	while (!st.stop_requested())
	{
		n = port.read_data(tmp, sizeof(tmp));

		for (i = 0; i < n; i++)
		{
			c = tmp[i];

			if (c == '\n')
			{
				{
					std::lock_guard<std::mutex> lock(data_mutex);
					latest_value = buffer;
				}
				buffer.clear();
			}
			else
			{
				buffer += c;
			}
		}
	}
}

void env_core::Controller::init_port()
{
	serial_port_thread = std::jthread([&](std::stop_token st)
	{
		serial_worker(st, port, latest_value, data_mutex);
	});
}

double env_core::Controller::calc_percentage_success()
{
	return (((double)stats.valid_data) / (stats.invalid_data + stats.valid_data)) * 100;
}

void env_core::Controller::decode_data_asyc()
{
	std::lock_guard<std::mutex> lock(data_mutex);
	std::stringstream ss(latest_value);

	std::string value;

	std::getline(ss, value, ';');
	recieved_data.success = std::stoi(value);

	std::getline(ss, value, ';');
	recieved_data.tempeture = std::stod(value) / 10.0;

	std::getline(ss, value, ';');
	recieved_data.humidity = std::stod(value) / 10.0;

	std::getline(ss, value, ';');
	recieved_data.error_code = std::stoi(value);
}

void env_core::Controller::init_server()
{
	server_http.set_base_dir("www");

	server_http.Get("/data", [&](const httplib::Request&, httplib::Response& res)
	{
		try
		{
			decode_data_asyc();
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << "\n";
			stats.invalid_data ++;
			return;
		}

		if (recieved_data.success)
		{
			stats.valid_data++;
			res.set_content(
						"{\"a\":\"" + std::format("{:.2f}", recieved_data.tempeture) +
						"\",\"b\":\"" + std::format("{:.2f}", recieved_data.humidity) + "\"}",
						"application/json"
						);
		}
		else
		{
			stats.invalid_data ++;
		}
	});

	server_thread = std::jthread([&](std::stop_token)
	{
		server_http.listen("0.0.0.0", 8080);
	});
}
