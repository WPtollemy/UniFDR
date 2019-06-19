#pragma once
#include <SFML/Graphics.hpp>
#include "Plane.h"
#include "FDRServerNetwork.h"

class DataDisplay
{
private:
	struct Button {
		sf::RectangleShape buttonShape;
		sf::Text buttonText;
		bool isOver = false;
	};

public:
	DataDisplay(sf::RenderWindow& window, Plane plane, FDRServerNetwork&);
	~DataDisplay();

	sf::RenderWindow& window;

	void run();

private:

	void initialise();
	
	void update();
	void render();
	void handleInput();
	std::string currentDate();
	
	bool displayScreen = true;

	Plane plane;
	Button backButton;
	sf::Text backText;
	sf::Font font;

	sf::Text planeName;
	std::vector<sf::Text> values;

	std::string filePath;
	FDRServerNetwork& network;
};

