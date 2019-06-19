#pragma once
#include "Sensor.h"

class Speed: public Sensor
{
	private:
		double data = 280;

	public:
		virtual void update() {};	//Override
		double getData() { return data; };
};

