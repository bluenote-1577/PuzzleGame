#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <string>

class MainMenu
{
public:
	MainMenu();
	void drawScreen(sf::RenderWindow& window);
	void drawInstructions(sf::RenderWindow& window);
	void clickOccur(sf::RenderWindow& window);

	int gamestatus;

private:
	sf:: Text maintitle;
	sf:: Text timedbutton;
	sf:: Text instructionsbutton;
	sf:: Text instructions;
	sf:: Text reset;

	sf::RectangleShape timedshape;
	sf::RectangleShape instructions_shape;
	sf::RectangleShape back;

	sf::Font main_font;

	sf::Color buttonColour;

};


#endif