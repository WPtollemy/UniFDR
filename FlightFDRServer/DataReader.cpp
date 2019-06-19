#include "stdafx.h"

/**
#include "DataReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <ctime>

bool DataStorer::readData(std::string path) {

	std::ofstream reader(path + "/" + currentDate() += ".txt", std::ios::app);

	if (!reader) {
		std::cerr << "Error opening file" << std::endl;
		return false;
	}

	
}

std::string	DataStorer::currentDate() {
	std::string str = "-";
	std::stringstream sstr;

	// current date/time based on current system
	time_t t;
	struct tm timePtr;
	time(&t);
	localtime_s(&timePtr, &t);

	sstr << timePtr.tm_mday;
	sstr << str;
	sstr << timePtr.tm_mon;
	sstr << str;
	sstr << timePtr.tm_year + 1900;

	return sstr.str();
}

/**/