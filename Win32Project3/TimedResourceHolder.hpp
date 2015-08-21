#ifndef TIMED_HPP
#define TIMED_HPP

#include <SFML/Graphics.hpp>
#include <string>


class TimedResourceHolder
{

public:
	TimedResourceHolder();
	void changeScore(int score);
	void changeComboUpdate(int comboUpdate);
	void changeScoreUpdate(int scoreUpdate);
	void gamestatus_changeString (std::string string);
	void drawAll( sf:: RenderTarget& window, sf::RenderStates state);
	sf::RectangleShape reset_button;


private:

	sf::Font main_font;

	sf::Text display;
	sf::Text score;
	sf::Text reset;
	sf::Text gamestatus;
	sf::Text combo_display;

	std::string s;
	std::string combo_update;
	std::string score_update;

};

#endif