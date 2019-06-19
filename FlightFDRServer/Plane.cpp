#include "stdafx.h"
#include "Plane.h"
#include <iostream>


Plane::Plane()
{
	timeRunning = std::clock();
}


Plane::~Plane()
{
}

void Plane::setFlightNumber(std::string flight)
{
	flightNumber = flight;
}

void Plane::setFuelLevel(double fuel)
{
	this->fuelLevel = fuel;
}

void Plane::setSpeed(float speed)
{
	this->speed = speed;
}

void Plane::setPressureAltitude(double altitude)
{
	this->pressureAltitude = altitude;
}

void Plane::setLatitude(float lati)
{
	this->location.latitude = lati;
}

void Plane::setLongitude(float longi)
{
	this->location.longitude = longi;
}

void Plane::setTime(std::clock_t time)
{
	timeRunning = time;
}

//Getters
std::string Plane::getFlightNumber()
{
	return flightNumber;
}

double Plane::getFuelLevel()
{
	return fuelLevel;
}

float Plane::getSpeed()
{
	return speed;
}

double Plane::getPressureAltitude()
{
	return pressureAltitude;
}

float Plane::getLatitude()
{
	return location.latitude;
}

float Plane::getLongitude()
{
	return location.longitude;
}

int Plane::lastPacketTime() 
{
	std::clock_t currentTime = std::clock();
	int timeElapsed = double(currentTime - timeRunning) / CLOCKS_PER_SEC;
	return timeElapsed;
}

void Plane::restartTime() 
{
	this->timeRunning = std::clock();
}