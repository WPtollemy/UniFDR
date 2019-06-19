#pragma once
#include "Sensor.h"

class Location: public Sensor
{
	public:
		struct LocationStruct {
			float longitude = 0.4543;
			float latitude = 51.4700;
		};

private:
	LocationStruct loc;

public:
	virtual void update() { if (loc.latitude > 40.6413) { loc.latitude -= 0.036096; }
								if (loc.longitude < 73.7781) { loc.longitude += 0.2444126; }};
	LocationStruct getData() { return loc; };
};

