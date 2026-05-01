//============================================================================
// Name        : MainSource.cpp
// Author      : Riyufuchi
// Created on  : Jul 13, 2020
// Last Edit   : Dec 04, 2025
// Description : This is programs main
//============================================================================

#include "controller/controller.h"

int main(int argc, char** argv)
{
	env_core::Controller controller;
	controller.print_header();
	controller.init();
	return 0;
}
