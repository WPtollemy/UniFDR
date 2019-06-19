#pragma once

#include "Alarm.h"
#include <string>

class Plane
{
public:
	struct LocationStruct {
		float longitude = 0.4543;
		float latitude = 51.4700;
	};

public:
	Plane();
	~Plane();

private:
	Alarm NormalAlarm = Alarm(sf::Color::Green, "Normal");
	Alarm WarningAlarm = Alarm(sf::Color::Yellow, "Warning");
	Alarm SevereAlarm = Alarm(sf::Color(255,140,0), "Severe");
	Alarm CriticalAlarm = Alarm(sf::Color::Red, "Critical");

	std::string flightNumber;
	double fuelLevel;
	float speed;
	double pressureAltitude;
	LocationStruct location;

	std::clock_t timeRunning;

	Alarm status = NormalAlarm;

public:
	void setFlightNumber(std::string);
	void setFuelLevel(double fuel);
	void setSpeed(float speed);
	void setPressureAltitude(double altitude);
	void setLatitude(float lati);
	void setLongitude(float longi);
	void setTime(std::clock_t time);

	void updateAllValues(Plane);

	void setStatusNormal() { this->status = NormalAlarm; };
	void setStatusWarning() { this->status = WarningAlarm; };
	void setStatusSevere() { this->status = SevereAlarm; };
	void setStatusCritical() { this->status = CriticalAlarm; };

	std::string getFlightNumber();
	double getFuelLevel();
	float getSpeed();
	double getPressureAltitude();
	float getLatitude();
	float getLongitude();
	std::clock_t getTime();

	int lastPacketTime();
	void restartTime();

	Alarm getStatus() { return status; };

};

