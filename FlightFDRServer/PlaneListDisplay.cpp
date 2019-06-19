#include "stdafx.h"
#include "PlaneListDisplay.h"
#include "DataDisplay.h"
#include <iostream>


PlaneListDisplay::PlaneListDisplay(sf::RenderWindow& window, FDRServerNetwork& network)
	: window(window)
	, network(network)
{
	//Initialse the start for the buttons/button positions
	planeButtonList.push_back(planeOne);
	planeList.push_back(testPlane1);

	//Main program
	font.loadFromFile("res/regular.otf");
	initialiseWindow();

	//Set the title
	title.setString("Planes currently in flight");
	title.setFont(font);
	title.setCharacterSize(40);
	title.setFillColor(sf::Color::White);
	bounds = title.getLocalBounds();
	title.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2);
	title.setPosition(window.getSize().x / 2, 50);
}


PlaneListDisplay::~PlaneListDisplay()
{
}

//Set up the window
void PlaneListDisplay::initialiseWindow()
{
	//Clear screen
	window.clear(sf::Color::Black);

	//Initialise button text names
	for (int i = 0; i < planeList.size(); i++) {
		planeNames.push_back(sf::Text());
		planeNames[i].setString(planeList[i].getFlightNumber());
		planeNames[i].setFont(font);
	}

	//Set the first button
	planeButtonList[0].buttonShape.setSize(buttonSize);
	planeButtonList[0].buttonShape.setOrigin(buttonOrigin);
	planeButtonList[0].buttonShape.setPosition(window.getSize().x / 6, window.getSize().y / 10);

	//Set the word/text alarm
	bounds = alarmTxt.getLocalBounds();
	alarmTxt.setString("Status: ");
	alarmTxt.setFont(font);
	alarmTxt.setCharacterSize(25);
	alarmTxt.setFillColor(sf::Color::White);
	alarmTxt.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2);

	//Set the alarm dot
	alarmDot.setRadius(10);
	alarmDot.setFillColor(sf::Color(200,200,200));
	/**/
}

//Render the screen. The buttons, button text, and window
void PlaneListDisplay::render()
{
	window.clear(sf::Color(30,30,30));
	
	window.draw(title);

	for (int i = 1; i < planeButtonList.size(); i++) {
		window.draw(planeButtonList[i].buttonShape);
		window.draw(planeButtonList[i].buttonText);

		alarmTxt.setPosition(planeButtonList[i].buttonShape.getPosition().x + planeButtonList[i].buttonShape.getSize().x + 75, planeButtonList[i].buttonShape.getPosition().y - planeButtonList[i].buttonShape.getSize().y / 2);
		alarmDot.setPosition(alarmTxt.getPosition().x + alarmTxt.getLocalBounds().width + 50, alarmTxt.getPosition().y + alarmTxt.getLocalBounds().height / 2);
		alarmDot.setFillColor(planeList[i].getStatus().alarmColour);

		window.draw(alarmTxt);
		window.draw(alarmDot);
	}

	window.display();
}

//Check mouse position and if it's over a button set isOver to true for the button, else false
void PlaneListDisplay::handleInput() 
{
	sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y);

	for (int i = 0; i < planeButtonList.size(); i++) {
		if (planeButtonList[i].buttonShape.getGlobalBounds().contains(mousePos)) {
			planeButtonList[i].isOver = true;
		}else
			if (planeButtonList[i].isOver)
				planeButtonList[i].isOver = false;
	}
}

//Set the outline of a button when mouse isOver
void PlaneListDisplay::update()
{
	for (int i = 1; i < planeButtonList.size(); i++) {
		if (planeButtonList[i].isOver)
			planeButtonList[i].buttonShape.setOutlineThickness(3);
		else
			planeButtonList[i].buttonShape.setOutlineThickness(0);
	}

	for (Plane plane : network.refresh()) {
		tempPlane = plane;
		planeToAdd = true;

		for (int i = 0; i < planeList.size(); i++) {
			if (plane.getFlightNumber() == planeList[i].getFlightNumber()) {
				planeList[i] = plane;
				planeToAdd = false;
				break;
			}
			else
				planeToAdd = true;
		}
		if (planeToAdd)
			planeList.push_back(tempPlane);
	}

	if (planeButtonList.size() != planeList.size()) {
		for(int i = 0; i < (planeList.size() - planeButtonList.size()); i++){
			Button button;
			planeButtonList.push_back(button);

			sf::Text text;
			planeNames.push_back(text);
		}

		for (int i = 1; i < planeList.size(); i++) {
			
			//Button look and placements
			planeButtonList[i].buttonShape.setSize(buttonSize);
			planeButtonList[i].buttonShape.setOrigin(buttonOrigin);
			planeButtonList[i].buttonShape.setPosition(planeButtonList[i - 1].buttonShape.getPosition().x, planeButtonList[i - 1].buttonShape.getPosition().y + 50);
			planeButtonList[i].buttonShape.setFillColor(buttonColour);
			planeButtonList[i].buttonShape.setOutlineColor(buttonOutlineColour);

			//Button text look and placement
			planeNames[i].setString(planeList[i].getFlightNumber());
			planeButtonList[i].buttonText = planeNames[i];
			planeButtonList[i].buttonText.setFont(font);
			planeButtonList[i].buttonText.setCharacterSize(25);
			planeButtonList[i].buttonText.setFillColor(sf::Color::White);
			bounds = planeButtonList[i].buttonText.getLocalBounds();
			planeButtonList[i].buttonText.setOrigin((bounds.left + bounds.width) / 2, (bounds.top + bounds.height) / 2 + 3);
			planeButtonList[i].buttonText.setPosition(planeButtonList[i].buttonShape.getPosition());
		}
	}

	for (int i = 0; i < planeList.size(); i++) {
		if (planeList[i].lastPacketTime() > 25)
			planeList[i].setStatusCritical();
		else if (planeList[i].lastPacketTime() > 15)
			planeList[i].setStatusSevere();
		else if (planeList[i].lastPacketTime() > 5)
			planeList[i].setStatusWarning();
		else
			planeList[i].setStatusNormal();
	}


}

//while; run, and polling an event
void PlaneListDisplay::run()
{
	sf::Event event;

	while (true) {

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
				for (int i = 0; i < planeButtonList.size(); i++)
					if (planeButtonList[i].isOver) {
						DataDisplay nextPage = DataDisplay(window, planeList[i], network);
						nextPage.run();
					}

				break;
			default:
				break;
			}
		}
		update();
		render();
	}
}