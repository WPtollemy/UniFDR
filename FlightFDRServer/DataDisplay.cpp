#include "stdafx.h"
#include "DataDisplay.h"
#include <sstream>
#include <iostream>


DataDisplay::DataDisplay(sf::RenderWindow& window, Plane plane, FDRServerNetwork& network)
	: window(window)
	, plane(plane)
	, network(network)
{

	for (int i = 0; i <= 6; i++) {
		sf::Text text;
		values.push_back(text);
	}

	initialise();
}


DataDisplay::~DataDisplay()
{
}

void DataDisplay::initialise()
{
	//Clear screen
	window.clear(sf::Color::White);

	//Initialise font and text
	font.loadFromFile("res/gravityBook.otf");
	backText.setString("Back");
	backText.setFont(font);

	//Needed to set the button text
	sf::FloatRect bounds;

	//Set back button
	backButton.buttonShape.setSize(sf::Vector2f(150, 30));
	backButton.buttonShape.setOrigin(sf::Vector2f(75, 15));
	backButton.buttonShape.setPosition(window.getSize().x / 12, window.getSize().y * 0.95);
	backButton.buttonShape.setFillColor(sf::Color::Black);
	backButton.buttonShape.setOutlineColor(sf::Color(50, 50, 50));
	backButton.buttonText = backText;
	backButton.buttonText.setCharacterSize(25);
	backButton.buttonText.setFillColor(sf::Color::White);
	bounds = backButton.buttonText.getLocalBounds();
	backButton.buttonText.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2 + 3);
	backButton.buttonText.setPosition(backButton.buttonShape.getPosition());

	//Set title
	planeName.setString(plane.getFlightNumber());
	planeName.setFont(font);
	planeName.setCharacterSize(40);
	planeName.setFillColor(sf::Color::White);
	planeName.setPosition(50, 20);

	//Set text of the values
	values[0].setString("Fuel Level:  " + std::to_string(plane.getFuelLevel()));
	values[1].setString("Speed:  " + std::to_string(plane.getSpeed()));
	values[2].setString("Pressure Altitude:  " + std::to_string(plane.getPressureAltitude()));
	values[3].setString("Latitude:  " + std::to_string(plane.getLatitude()));
	values[4].setString("Longitude:  " + std::to_string(plane.getLongitude()));
	values[5].setString("Status:  " + plane.getStatus().description);
	values[6].setString("Time since last packet:  " + std::to_string(plane.lastPacketTime()) + "  seconds");
	/**/
	/**/
	for (int i = 0; i < values.size(); i++) {
		values[i].setFont(font);
		values[i].setCharacterSize(25);
		values[i].setFillColor(sf::Color::White);
		if (i == 0)
			values[i].setPosition(400, 30);
		else
			values[i].setPosition(values[i-1].getPosition().x, values[i - 1].getPosition().y + 50);
	}/**/

}

void DataDisplay::render()
{
	window.clear(sf::Color(30, 30, 30));

	window.draw(backButton.buttonShape);
	window.draw(backButton.buttonText);
	window.draw(planeName);

	//Set text of the values
	values[0].setString("Fuel Level:  " + std::to_string(plane.getFuelLevel()));
	values[1].setString("Speed:  " + std::to_string(plane.getSpeed()));
	values[2].setString("Pressure Altitude:  " + std::to_string(plane.getPressureAltitude()));
	values[3].setString("Latitude:  " + std::to_string(plane.getLatitude()));
	values[4].setString("Longitude:  " + std::to_string(plane.getLongitude()));
	values[5].setString("Status:  " + plane.getStatus().description);
	values[5].setFillColor(plane.getStatus().alarmColour);
	values[6].setString("Time since last packet:  " + std::to_string(plane.lastPacketTime()) + "  seconds");
	values[6].setFillColor(plane.getStatus().alarmColour);

	for (int i = 0; i < values.size(); i++) {
		window.draw(values[i]);
	}

	window.display();
}

void DataDisplay::handleInput()
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	if (backButton.buttonShape.getGlobalBounds().contains(mousePos))
		backButton.isOver = true;
	else
		backButton.isOver = false;
}

void DataDisplay::update()
{
	if (backButton.isOver)
		backButton.buttonShape.setOutlineThickness(3);
	else
		backButton.buttonShape.setOutlineThickness(0);

	for (Plane plane : network.refresh()) {
		if (plane.getFlightNumber() == this->plane.getFlightNumber())
			this->plane = plane;
	}

	if (plane.lastPacketTime() > 25)
		plane.setStatusCritical(); 
	else if (plane.lastPacketTime() > 15)
		plane.setStatusSevere();
	else if (plane.lastPacketTime() > 5)
		plane.setStatusWarning();
	else
		plane.setStatusNormal();
}

void DataDisplay::run()
{
	sf::Event event;

	while (displayScreen) {

		while (window.pollEvent(event)) {

			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				handleInput();
				break;
			case sf::Event::MouseButtonReleased:
				if(backButton.isOver)
					displayScreen = false;
				break;
			default:
				break;
			}
		}
		update();
		render();
	}
}

std::string	DataDisplay::currentDate()
{
	std::string str = "-";
	std::stringstream sstr;

	// current date/time based on current system
	time_t t;
	struct tm timePtr;
	time(&t);
	localtime_s(&timePtr, &t);

	sstr << timePtr.tm_mday;
	sstr << str;
	sstr << timePtr.tm_mon;
	sstr << str;
	sstr << timePtr.tm_year + 1900;

	return sstr.str();
}