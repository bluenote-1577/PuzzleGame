#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Block.hpp"
#include "Blocktree.hpp"
#include "TimedResourceHolder.hpp"
#include "MainMenu.hpp"
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
	TimedResourceHolder timed_resources;
	sf::FloatRect reset_bounds = timed_resources.reset_button.getGlobalBounds();
	sf::FloatRect menu_bounds = timed_resources.menu_button.getGlobalBounds();
	sf::Clock clock;
	sf::Clock drop_clock;
	sf:: Time time;
	sf:: Time drop_time;
	Blocktree mainTree;
	MainMenu mainmenu;
	
	
	while (window.isOpen())
	{
		
		sf::Event event;
		while(mainmenu.gamestatus != 1 && window.isOpen()){
			

			while(window.pollEvent(event)){
				if (event.type == sf::Event::Closed )
					window.close();
				if (event.type == sf::Event::MouseButtonPressed)
					mainmenu.clickOccur(window);
			}
			window.clear(lightblue);
			mainmenu.drawScreen(window);
			mainTree.drop_clock.restart();
			mainTree.timerClock.restart();
			window.display();
		}
		
		
		// everything below is timed puzzle game
		time = clock.restart();
		timed_resources.changeScore(mainTree.score);

		
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed )
				window.close();

			if(event.type == sf::Event::MouseButtonPressed && mainTree.is_game_over() != true)
				
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
					if(mainTree.clickOccur_clear(window,reset_bounds, menu_bounds, mainmenu)){
						timed_resources.changeComboUpdate(mainTree.combo_count-1);
						timed_resources.changeScoreUpdate(mainTree.last_score);
					}
				}

				else { 
					
					if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						int id_to_swap = mainTree.clickOccur_swap(window,reset_bounds, menu_bounds, mainmenu);
						int id_to_swap2;

						while (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						
							time = clock.restart();
							timed_resources.changeScore(mainTree.score);
							mainTree.updateGame_blocks(time);
							window.clear(lightblue);
							mainTree.drawTree(window, state);
							timed_resources.drawAll(window,state,mainTree);
							id_to_swap2 = mainTree.clickOccur_swap(window,reset_bounds, menu_bounds, mainmenu);
							if (mainTree.is_game_over() == true)
								goto ifGameEnds;

							if(id_to_swap == -2 || id_to_swap2 == -2){
								clock.restart();
							}

							else if (id_to_swap >0 && id_to_swap2 >0)
								mainTree.draw_select(id_to_swap,id_to_swap2,window,state);
							timed_resources.changeComboUpdate(mainTree.combo_count-1);
							window.display();
							if (mainmenu.gamestatus == 0) break;

					}
			
					if(mainTree.swap_colours(id_to_swap,id_to_swap2) == 0)
						timed_resources.gamestatus_changeString("Invalid Swap!");
					else timed_resources.gamestatus_changeString("");
						timed_resources.changeComboUpdate(mainTree.combo_count-1);
					}
				}
			if (event.type == sf::Event::MouseButtonPressed && mainTree.is_game_over() == true){
			
				if(mainTree.gameover_reset(window,reset_bounds,menu_bounds,mainmenu));
				timed_resources.gamestatus_changeString("");
			}
		}


		ifGameEnds:
		mainTree.updateGame_blocks(time);
		window.clear(lightblue);
		mainTree.drawTree(window, state);
		timed_resources.drawAll(window,state,mainTree);
		timed_resources.changeComboUpdate(mainTree.combo_count-1);
	
		if (mainTree.is_game_over() == true){
			if(mainTree.highScore_recorded == false){
				if(timed_resources.write_highScore())
				mainTree.highScore_recorded =true;
			}
			if(mainTree.highScore_recorded == false)
			timed_resources.gamestatus_changeString("You lost!\n Click reset\n to start again\n High Score\n Error!");

			else timed_resources.gamestatus_changeString("You lost!\n Click reset\n to start again\n High Score\n Recorded!");
			mainTree.drop_clock.restart();

			window.display();
			
		
			
		}
	
		else{
			window.display();
		}
	}

}

