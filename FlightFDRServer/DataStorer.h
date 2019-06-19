#pragma once

#include <string>

class DataStorer {

	public:
		static bool logData(std::string, std::string);

	private:
		static std::string currentDate();
};