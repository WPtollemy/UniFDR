#pragma once
#include <SFML/Graphics.hpp>
#include "Plane.h"
#include "FDRServerNetwork.h"


class PlaneListDisplay
{
private:
	struct Button {
		sf::RectangleShape buttonShape;
		sf::Text buttonText;
		bool isOver = false;
	};

public:
	PlaneListDisplay(sf::RenderWindow&, FDRServerNetwork&);
	~PlaneListDisplay();

	sf::RenderWindow& window;

	void run();

	//Other methods/variables
	std::vector<Button> planeButtonList;
	std::vector<Plane> planeList;
	std::vector<sf::Text> planeNames;

	sf::Font font;

private:
	//Window Methods
	void initialiseWindow();
	void render();
	void update();
	void handleInput();

	//Variables
	FDRServerNetwork& network;
	Plane tempPlane;
	bool planeToAdd;

	//Visual Attributes
	const sf::Vector2f buttonSize = sf::Vector2f(200, 30);
	const sf::Vector2f buttonOrigin = sf::Vector2f(100, 15);
	const sf::Color buttonColour = sf::Color(150,150,175);
	const sf::Color buttonOutlineColour = sf::Color(255,255,255);

	sf::Text alarmTxt;
	sf::CircleShape alarmDot;
	sf::Text title;

	//Needed to set the button text
	sf::FloatRect bounds;

	//Testing Data
	Button planeOne;
	Plane testPlane1;
};

