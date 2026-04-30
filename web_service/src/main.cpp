//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : Jul 13, 2020
// Last Edit   : Dec 04, 2025
// Description : This is programs main
//============================================================================

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <map>
#include <thread>

#include "external/httplib.h"

#include "ports/serial_port.hpp"

#include "consolelib/tools/console_tools.h"

void serial_worker(std::stop_token st, SerialPort& port, std::string& latest_value, std::mutex& data_mutex);

int main(int argc, char** argv)
{
	std::cout << "Web service Ardo v1.0 - beta\n";

	std::mutex data_mutex;
	std::string latest_value;
	std::string tempeture = "?";
	std::string humidity = "?";
	std::string success = "?";
	std::string error_code = "?";



	int valid_data = 0;
	int invalid_data = 0;

	httplib::Server server_http;

	server_http.Get("/data", [&](const httplib::Request&, httplib::Response& res)
	{
		std::lock_guard<std::mutex> lock(data_mutex);
		std::stringstream ss(latest_value);

		std::getline(ss, success, ';');
		std::getline(ss, tempeture, ';');
		std::getline(ss, humidity, ';');
		std::getline(ss, error_code, ';');

		double temp = std::stod(tempeture) / 10.0;
		double hum =  std::stod(humidity) / 10.0;

		tempeture = std::to_string(temp).substr(0, 4) + " °C";
		humidity = std::to_string(hum).substr(0, 4) + " %";

		if (success == "1")
		{
			valid_data++;
			res.set_content(
						"{\"a\":\"" + tempeture +
						"\",\"b\":\"" + humidity + "\"}",
						"application/json"
						);
		}
		else
		{
			invalid_data ++;
			std::cout << "Error for line: " << latest_value << "\n\n";
		}

		std::cout << valid_data << " : " << invalid_data << " => "<< (((double)valid_data) / (invalid_data + valid_data)) * 100 << " %" << "\n\n";
	});

	// Serve files from ./www folder
	server_http.set_base_dir("www");

	std::jthread server_thread([&](std::stop_token st) {
		server_http.listen("0.0.0.0", 8080);
	});


	SerialPort port;

	std::jthread serial_port_thread([&](std::stop_token st) {
		serial_worker(st, port, latest_value, data_mutex);
	});

	consolelib::console_tools::wait_for_enter();

	serial_port_thread.request_stop();
	server_thread.request_stop();
	server_http.stop();

	std::cout << "Server exited with code 0\n";
	return 0;
}

void serial_worker(std::stop_token st, SerialPort& port, std::string& latest_value, std::mutex& data_mutex)
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
