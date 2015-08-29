#ifndef TIMED_HPP
#define TIMED_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include "Blocktree.hpp"
#include <list>
#include <cstdlib>
#include <sstream>
#include <iomanip>

/**
				The TimedResourceHolder Class

This class holds all the resources that are needed when the actual game is playing.
e.g. score texts, changing scores based on the game, writing high scores, buttons, etc.
Getters and setters are used for changing private members.



**/
class TimedResourceHolder
{

public:
	TimedResourceHolder();
	void changeScore(int score);
	void changeComboUpdate(int comboUpdate);
	void changeScoreUpdate(int scoreUpdate);
	void gamestatus_changeString (std::string string);
	void drawAll( sf:: RenderTarget& window, sf::RenderStates state, Blocktree& mainTree);
	void timerUpdate(Blocktree& mainTree);
	sf::RectangleShape reset_button;
	sf::RectangleShape menu_button;
	bool write_highScore();
	void changeDropTime(float drop_time);

private:

	sf::Font main_font;

	sf::Text display;
	sf::Text score;
	sf::Text reset;
	sf::Text gamestatus;
	sf::Text combo_display;
	sf::Text menu;
	sf::Text timer;
	sf::Text dropTime;

	std::string s;
	std::string combo_update;
	std::string score_update;
	std::string time_update;
	
	std::list <int> score_container;
	std::list <int> time_container;


};

#endif