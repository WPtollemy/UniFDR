// FlightFDRServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "FDRServerNetwork.h"
#include <SFML/Graphics.hpp>
#include "PlaneListDisplay.h"

sf::RenderWindow window(sf::VideoMode(900, 600), "Flight System Controller");

int main()
{
	std::cout << "Hello world!" << std::endl;

	FDRServerNetwork net;
	net.run();

	PlaneListDisplay mainMenu = PlaneListDisplay(window, net);
	mainMenu.run();

	while (true) {
		//Nothing
	}

    return 0;
}

