// FlightFDRClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "FDRController.h"
#include <ctime>
#include <cstdlib>

int main()
{
	std::srand(std::time(0));
	FDRController controller;
	controller.run();
    return 0;
}

