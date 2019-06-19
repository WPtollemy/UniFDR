#pragma once
#include "Sensor.h"

class PressureAltitude: public Sensor
{
	private:
		double data = 25000;

	public:
		virtual void update() { if (data < 30000) { data += 500; } };	//Override
		double getData() { return data; };
};

