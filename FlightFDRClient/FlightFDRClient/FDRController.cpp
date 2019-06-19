#include "stdafx.h"
#include "FDRController.h"
#include <thread>
#include <chrono>


FDRController::FDRController()
{
	
}


FDRController::~FDRController()
{
}

void FDRController::initialiseFlight()
{
	
}

void FDRController::run() {
	bool isRunning = true;

	while(isRunning) {

		//Update the test data and send
		updateSensors();
		if (!checkForBadData())
			networkSend.sendData(serialise());
		else
			isRunning = false;


		//Sets delay for data transmission
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
}

void FDRController::updateSensors() {

	fuel.update();
	speed.update();
	altitude.update();
	loc.update();
}

std::string FDRController::serialise() {

	std::stringstream sstr;

	sstr << flightNumber << " " << fuel.getData() << " " << speed.getData() << " " << altitude.getData();
	sstr << " " << loc.getData().latitude << " " << loc.getData().longitude;

	

	return sstr.str();
}

bool FDRController::checkForBadData() {

	if (fuel.getData() == 0)
		return true;
	else if (speed.getData() < 100)
		return true;
	else if (altitude.getData() < 1000)
		return true;
	else if (loc.getData().latitude < -90 || loc.getData().latitude > 90)
		return true;
	else if (loc.getData().longitude < -180 || loc.getData().longitude > 180)
		return true;
	else
		return false;

	return false;
}
