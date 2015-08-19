#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Block.hpp"
#include "Blocktree.hpp"
#include <string>
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <thread>



int main(void) {

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	sf::RenderWindow window(sf::VideoMode (600,400), "My Window");
	window.setFramerateLimit(60);
	sf::RenderStates state;

	
	sf:: Color lightblue(230,230,250,0);
	sf::Font main_font;
	
	main_font.loadFromFile("Buttons/ClaphappyLight.ttf");
	sf::Text display;
	sf::Text score;
	sf::Text reset;
	sf::Text gamestatus;
	sf::Text combo_display;

	std::string s;
	std::string combo_update = "0";
	std::string score_update;
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

	reset.setFont(main_font);
	reset.setPosition(440.0,50.0);
	reset.setColor(sf::Color::Black);
	reset.setString("Reset");
	reset.setStyle(0);

	combo_display.setFont(main_font);
	combo_display.setPosition(50.0,20);
	combo_display.setColor(sf::Color::Black);
	combo_display.setStyle(0);
	combo_display.setString("Combo : 0");

	sf::RectangleShape reset_button(sf::Vector2f(50.0,40.0));
	reset_button.setOrigin(-440.0,-90.0);
	reset_button.setOutlineColor(sf::Color::Black);
	reset_button.setOutlineThickness(2.0);
	reset_button.setFillColor(sf::Color::White);
	sf::FloatRect reset_bounds = reset_button.getGlobalBounds();
	sf::Clock clock;
	sf::Clock drop_clock;
	sf:: Time time;
	sf:: Time drop_time;
	Blocktree mainTree;
	int drops = 0;
	
	
	
	while (window.isOpen())
	{
		time = clock.restart();
		s = std::to_string(mainTree.score);
		score.setString(s);
		

		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed )
				window.close();

			if(event.type == sf::Event::MouseButtonPressed && mainTree.is_game_over() != true)
				
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::C)){

				if(mainTree.clickOccur_clear(window,reset_bounds)){
				
				combo_update = std::to_string(mainTree.combo_count - 1);
				score_update = std::to_string(mainTree.last_score);
				gamestatus.setString( "+ " + score_update + "points!");
				}
				
				}
				else { if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
					int id_to_swap = mainTree.clickOccur_swap(window,reset_bounds);
					
					
					int id_to_swap2;

				
					while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{

						time = clock.restart();
						s = std::to_string(mainTree.score);
						score.setString(s);

						mainTree.updateGame_blocks(time);
						//if( mainTree.updateGame_drop(drop_clock.getElapsedTime(), drops) == true)
						//	drop_clock.restart();
						window.clear(lightblue);
						mainTree.drawTree(window, state);
						window.draw(display);
						window.draw(combo_display);
						window.draw(score);
						window.draw(reset_button);
						window.draw(reset);
						window.draw(gamestatus);
						mainTree.drawTree(window,state);
						id_to_swap2 = mainTree.clickOccur_swap(window,reset_bounds);
						if (mainTree.is_game_over() == true)
							goto ifGameEnds;

						if(id_to_swap == -2 || id_to_swap2 == -2){
							clock.restart();
							drops = 0;
						}

						else if (id_to_swap >0 && id_to_swap2 >0)
							mainTree.draw_select(id_to_swap,id_to_swap2,window,state);
						combo_display.setString("Combo : " + combo_update);
						window.display();

							
					}
					
					if(mainTree.swap_colours(id_to_swap,id_to_swap2) == 0)
						gamestatus.setString("Invalid swap!");
					else {gamestatus.setString("");
						combo_update = std::to_string(mainTree.combo_count - 1);}

					}
				}
			if (event.type == sf::Event::MouseButtonPressed && mainTree.is_game_over() == true){
				gamestatus.setString("");
				mainTree.gameover_reset(window,reset_bounds);
			}
		}

		ifGameEnds:
		mainTree.updateGame_blocks(time);
		if( mainTree.updateGame_drop(drop_clock.getElapsedTime(), drops) == true)
			drop_clock.restart();
		window.clear(lightblue);
		mainTree.drawTree(window, state);
		window.draw(display);
		window.draw(score);
		window.draw(reset_button);
		window.draw(reset);
		window.draw(gamestatus);
		combo_display.setString("Combo : " + combo_update);
		window.draw(combo_display);
		if (mainTree.is_game_over() == true){
			gamestatus.setString("You lost!\n Click reset\n to start again");
			drops = 0;
			window.display();
			clock.restart();
			
		
			
		}
	
		else window.display();

	}

}

