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

/**

				Main Game Loop

This game loop controls everything that happens in the game. What gets
rendered, the logic, etc.


**/

int main(void) {


	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );				
	sf::RenderWindow window(sf::VideoMode (600,400), "ComboPuzzle");
	window.setFramerateLimit(60);
	sf::RenderStates state;
	sf:: Color lightblue(230,230,250,0);
	TimedResourceHolder timed_resources;
	sf::FloatRect reset_bounds = timed_resources.reset_button.getGlobalBounds();
	sf::FloatRect menu_bounds = timed_resources.menu_button.getGlobalBounds();
	sf::Clock clock;
	sf:: Time time;
	Blocktree mainTree;
	MainMenu mainmenu;
	
	
	while (window.isOpen())												//Main Loop, while the game is running this loop is occuring
	{
		
		sf::Event event;
		while(mainmenu.gamestatus != 1 && window.isOpen()){             //This loop is the main menu loop. Mainmenu.gamestatus represents what gets rendered. 
			while(window.pollEvent(event)){                             //This sub-loop only occurs when gamestatus != 1, i.e. we haven't clicked start.
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

																		
		while(window.pollEvent(event))								//checks to see if any event has occured. various functions are executed depending on the event below.
		{
			if (event.type == sf::Event::Closed )
				window.close();

			if(event.type == sf::Event::MouseButtonPressed && mainTree.is_game_over() != true)
				
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Keyboard::isKeyPressed(sf::Keyboard::C)){  //executes clickOccur_clear which checks the rows/columns and erases them.
					if(mainTree.clickOccur_clear(window,reset_bounds, menu_bounds, mainmenu)){
						timed_resources.changeComboUpdate(mainTree.combo_count-1);
						timed_resources.changeScoreUpdate(mainTree.last_score);
					}
				}

				else { 
					
					if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						int id_to_swap = mainTree.clickOccur_swap(window,reset_bounds, menu_bounds, mainmenu);  // this branch is for swapping. 
						int id_to_swap2;

						while (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
						
							time = clock.restart();
							timed_resources.changeScore(mainTree.score);
							timed_resources.changeDropTime(mainTree.updateGame_blocks(time));					// a compact version of the larger loop with rendering and updating
							window.clear(lightblue);															// occurs when the mouse is held down. 
							mainTree.drawTree(window, state);
							timed_resources.drawAll(window,state,mainTree);
							id_to_swap2 = mainTree.clickOccur_swap(window,reset_bounds, menu_bounds, mainmenu);
							if (mainTree.is_game_over() == true)
								goto ifGameEnds;

							if(id_to_swap == -2 || id_to_swap2 == -2){
								clock.restart();
							}

							else if (id_to_swap >-1 && id_to_swap2 >-1)
								mainTree.draw_select(id_to_swap,id_to_swap2,window,state);						// the blocks that are being clicked on render their selected sprites
							timed_resources.changeComboUpdate(mainTree.combo_count-1);
							window.display();
							if (mainmenu.gamestatus == 0) break;

					}
			
					if(mainTree.swap_colours(id_to_swap,id_to_swap2) == 0)										//colour swap occurs once the mouse button has been let go of
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
		timed_resources.changeDropTime(mainTree.updateGame_blocks(time));										//rendering occurs, updates occur.
		window.clear(lightblue);
		mainTree.drawTree(window, state);
		
		timed_resources.changeComboUpdate(mainTree.combo_count-1);
		timed_resources.drawAll(window,state,mainTree);
		
	 
		if (mainTree.is_game_over() == true){                                          //records the high score if it hasn't been recorded yet and the game is over
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

