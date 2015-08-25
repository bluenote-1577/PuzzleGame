#include <SFML/Graphics.hpp>
#include "TimedResourceHolder.hpp"

TimedResourceHolder :: TimedResourceHolder() : reset_button(sf::Vector2f(50.0,40.0)), menu_button(sf::Vector2f(50.0,40.0))
{

	main_font.loadFromFile("Buttons/ClaphappyLight.ttf");
	combo_update = "0";

	display.setFont(main_font);
	display.setPosition(50.0,60);
	display.setColor(sf::Color::Black);
	display.setString("Score");
	display.setStyle(0);

	gamestatus.setFont(main_font);
	gamestatus.setPosition(50,200);
	gamestatus.setColor(sf::Color::Black);
	gamestatus.setStyle(0);


	score.setFont(main_font);
	score.setPosition(50.0,95);
	score.setColor(sf::Color::Black);
	score.setStyle(0);
	score.setString(s);

	reset.setFont(main_font);
	reset.setPosition(440.0,50.0);
	reset.setColor(sf::Color::Black);
	reset.setString("Reset");
	reset.setStyle(0);

	combo_display.setFont(main_font);
	combo_display.setPosition(50.0,20);
	combo_display.setColor(sf::Color::Black);
	combo_display.setStyle(0);
	combo_display.setString("Combo : " + combo_update);

	reset_button.setOrigin(-440.0,-90.0);
	reset_button.setOutlineColor(sf::Color::Black);
	reset_button.setOutlineThickness(2.0);
	reset_button.setFillColor(sf::Color::White);

	menu_button.setPosition(440.0,180);
	menu_button.setOutlineColor(sf::Color::Black);
	menu_button.setOutlineThickness(2.0);
	menu_button.setFillColor(sf::Color::White);

	menu.setFont(main_font);
	menu.setPosition(440.0,140);
	menu.setColor(sf::Color::Black);
	menu.setString("Menu");
	menu.setStyle(0);


	timer.setFont(main_font);
	timer.setPosition(440,230);
	timer.setColor(sf::Color::Black);
	timer.setString("Timer : 0");
	menu.setStyle(0);
}


void TimedResourceHolder:: changeScore(int newScore)
{

	s = std::to_string(newScore);
	score.setString(s);
}

	
void TimedResourceHolder :: changeComboUpdate(int comboUpdate)
{
	combo_update = std::to_string(comboUpdate);
	combo_display.setString("Combo : " + combo_update);
}

void TimedResourceHolder ::changeScoreUpdate(int scoreUpdate)
{
	score_update = std::to_string(scoreUpdate);
	gamestatus.setString( "+ " + score_update + "points!");
}


void TimedResourceHolder ::gamestatus_changeString (std::string string)
{
	gamestatus.setString(string);
}

void TimedResourceHolder:: drawAll( sf:: RenderTarget& window, sf::RenderStates state, Blocktree& mainTree)
{
	if(mainTree.is_game_over() == false)
		timerUpdate(mainTree);
	
	window.draw(display);
	window.draw(combo_display);
	window.draw(score);
	window.draw(reset_button);
	window.draw(reset);
	window.draw(gamestatus);
	window.draw(menu_button);
	window.draw(menu);
	window.draw(timer);
}

void TimedResourceHolder:: timerUpdate(Blocktree& mainTree)

{
	time_update = std::to_string(static_cast<int>(mainTree.timerClock.getElapsedTime().asSeconds()));
	timer.setString("Timer : " + time_update);

}
bool TimedResourceHolder :: write_highScore()
{
	std::fstream myfile;
	myfile.open("high_scores.txt");
	if (myfile.fail())
		return false;

	

	return true;


}