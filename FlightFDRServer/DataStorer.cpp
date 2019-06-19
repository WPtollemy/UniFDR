#include "stdafx.h"
#include "DataStorer.h"
#include <fstream>
#include <iostream>
#include <ctime>
#include <sstream>
#include <tchar.h>
#include <Windows.h>


bool DataStorer::logData(std::string flightNum, std::string data) {

	flightNum = "Planes/" + flightNum;

	if (CreateDirectory(flightNum.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError()) {

		std::ofstream writer(flightNum + "/" + currentDate() += ".txt", std::ios::app); //append to flight num file

		if (!writer) {
			std::cerr << "Error opening file" << std::endl;
			return false;
		}

		writer << data << std::endl;

		return true;
	}

	return false;
}

std::string	DataStorer::currentDate() {
	std::string str = "-";
	std::stringstream sstr;

	// current date/time based on current system
	time_t t;
	struct tm timePtr;
	time(&t);
	localtime_s(&timePtr, &t);

	/* Timer References /**
	std::cout << "seconds= " << timePtr.tm_sec << std::endl;
	std::cout << "minutes = " << timePtr.tm_min << std::endl;
	std::cout << "hours = " << timePtr.tm_hour << std::endl;
	std::cout << "day of month = " << timePtr.tm_mday << std::endl;
	std::cout << "month of year = " << timePtr.tm_mon << std::endl;
	std::cout << "year = " << timePtr.tm_year << std::endl;
	std::cout << "weekday = " << timePtr.tm_wday << std::endl;
	std::cout << "day of year = " << timePtr.tm_yday << std::endl;
	std::cout << "daylight savings = " << timePtr.tm_isdst << std::endl;
	/**/

	sstr << timePtr.tm_mday;
	sstr << str;
	sstr << timePtr.tm_mon + 1;
	sstr << str;
	sstr << timePtr.tm_year + 1900;

	return sstr.str();
}