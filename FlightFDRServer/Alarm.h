/**/
#pragma once
#ifndef ALARM_H
#define ALARM_H

#include <string>
#include <SFML\Graphics.hpp>

class Alarm {
public:
	sf::Color alarmColour;
	std::string description;

	Alarm(sf::Color clr, std::string str) : alarmColour(clr)
		, description(str) {};
};

#endif // !ALARM_H
