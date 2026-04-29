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

#include "external/httplib.h"

int main(int argc, char** argv)
{
	httplib::Server server_http;


	// Serve files from ./www folder
	server_http.set_base_dir("www");

	/*svr.Get("/data", [](const httplib::Request&, httplib::Response& res){
		res.set_content(std::to_string(latestValue.load()), "text/plain");
	});*/

	server_http.listen("0.0.0.0", 8080);

	return 0;
}
