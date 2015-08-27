#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

class MainMenu
{
public:
	MainMenu();
	bool scanHighScores();
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
	sf:: Text highscores_text;
	sf:: Text highscores_title;
	sf:: Text highscores;
	sf:: Text hightimes;

	std::string score_time;
	std::string actual_scores;
	std::string actual_times;

	sf::RectangleShape timedshape;
	sf::RectangleShape instructions_shape;
	sf::RectangleShape back;
	sf::RectangleShape highscore_button;

	sf::Font main_font;

	sf::Color buttonColour;

	std::list <std::string> score_container;
	std::list <std::string> time_container;

	void setHighScores();

};


#endif