#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <list>

/**
					MainMenu class

The MainMenu class is a short and simple class that holds all the resources and logic behind the main screen.

					Appearance:

The sf:Text members hold text. The sf::RectangleShape members are the buttons for clicking that redirect the game.

					Screens :

int gamestatus represents that screen is being rendered. 1 = the puzzle game is being played, 0 = main screen displayed
2 = instructions screen, 3 = high score screen. When a button is clicked gamestatus switches and rendering depends on gamestatus.

					Highscores:

When the highscores button is clicked, a highscore screen will be displayed and the data will be read from
file "highscores.txt" in the puzzlegame folder. 
**/

class MainMenu
{
public:
	MainMenu();
	bool scanHighScores();
	void drawScreen(sf::RenderWindow& window);
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