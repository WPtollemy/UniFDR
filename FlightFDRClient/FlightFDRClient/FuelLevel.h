#pragma once
#include "Sensor.h"

class FuelLevel: public Sensor
{
	private:
		double data = 100;

	public:
		virtual void update() { data -= 0.25; };	//Override
		double getData() { return data; };
};

