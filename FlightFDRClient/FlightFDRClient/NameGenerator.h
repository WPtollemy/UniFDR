#pragma once
#include <string>
#include <vector>

class NameGenerator
{
private:
	const std::vector<std::string> start = {"KLM","BA","UAE","U2","VS","AA","SX"};

public:
	const std::string generateName() {
		std::string str = "";

		int first = std::rand() % start.size();
		str += start[first];

		for (int i = 0; i < 3; i++) {
			int toAdd = std::rand() % 10;
			str += std::to_string(toAdd);
		}

		std::cout << str << std::endl;
		return str;
	}
	
};

