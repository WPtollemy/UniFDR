#pragma once
#include "FuelLevel.h"
#include "Speed.h"
#include "PressureAltitude.h"
#include "Location.h"
#include "FDRClientNetwork.h"
#include <sstream>
#include <iostream>
#include "NameGenerator.h"

class FDRController
{
	private:
		FDRClientNetwork networkSend;

		std::string flightNumber = NameGenerator().generateName();;

		//Sensors
		FuelLevel fuel;
		Speed speed;
		PressureAltitude altitude;
		Location loc;

		//Methods
		void updateSensors();
		std::string serialise();
		bool checkForBadData();


	public:
		FDRController();
		~FDRController();

		void initialiseFlight();

		void run();
};

