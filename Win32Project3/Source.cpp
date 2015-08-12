#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "Block.hpp"
#include "Blocktree.hpp"
#include <string>
#define CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

/**int main()
{

	sf:: Texture texture[3];
	sf::RenderStates state;
	texture[0].loadFromFile("C:/Users/Owner/Desktop/Buttons/GJ_button_03.png");//pink
	texture[1].loadFromFile("C:/Users/Owner/Desktop/Buttons/GJ_button_02.png");//teal
	texture[2].loadFromFile("C:/Users/Owner/Desktop/Buttons/GJ_button_01.png");//green

	
	
	sf::RenderWindow window(sf::VideoMode (600,400), "My Window");
	Block newBlock(texture[1]);
	
	sf:: Sprite block[9];
	 srand(time(NULL));
	for( int i = 0; 3>i; i++){

		float ypos = (float)(-180-i*40);

		for ( int b = 0; 3>b; b++)
		{
		int random = rand() % 3;

		if (random == 0)
			block[b+ i*3].setTexture(texture[0]);
		if (random == 1)
			block[b+ i*3].setTexture(texture[1]);
		if (random == 2)
			block[b+i*3].setTexture(texture[2]);

		float xpos = (float)(-240-b*40);
	

		block[b+i*3].setOrigin(xpos,ypos);
		}
	}
	while (window.isOpen())
	{
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type = sf::Event::Closed)
				window.close();
		}

		window.clear();
		for(int i = 0; i<9; i++)
			window.draw(block[i]);
		window.draw(newBlock);
		window.display();
		
		
	}



}**/


int main(void) {

	_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	sf::RenderWindow window(sf::VideoMode (600,400), "My Window");
	sf::RenderStates state;

	Blocktree mainTree;
	sf:: Color lightblue(230,230,250,0);
	sf::Font main_font;
	
	main_font.loadFromFile("Buttons/ClaphappyLight.ttf");
	sf::Text display;
	sf::Text score;
	sf::Text reset;

	std::string s;
	display.setFont(main_font);
	display.setPosition(240.0,50.0);
	display.setColor(sf::Color::Black);
	display.setString("Your score :");
	display.setStyle(0);

	

	score.setFont(main_font);
	score.setPosition(240.0,80.0);
	score.setColor(sf::Color::Black);
	score.setStyle(0);

	reset.setFont(main_font);
	reset.setPosition(440.0,50.0);
	reset.setColor(sf::Color::Black);
	reset.setString("Reset");
	reset.setStyle(0);

	sf::RectangleShape reset_button(sf::Vector2f(50.0,40.0));
	reset_button.setOrigin(-440.0,-90.0);
	reset_button.setOutlineColor(sf::Color::Black);
	reset_button.setOutlineThickness(2.0);
	reset_button.setFillColor(sf::Color::White);
	sf::FloatRect reset_bounds = reset_button.getGlobalBounds();

	while (window.isOpen())
	{
	

		s = std::to_string(mainTree.score);
		score.setString(s);
		mainTree.updateScan();
		sf::Event event;
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if(event.type == sf::Event::MouseButtonPressed)
				mainTree.clickOccur(window,display,reset_bounds);
			//if (event.type = sf::Event::MouseButtonPressed)
			// implementation of blocktree.update();
		}

		window.clear(lightblue);
		mainTree.drawTree(window, state);
		window.draw(display);
		window.draw(score);
		window.draw(reset_button);
		window.draw(reset);
		window.display();
	}

}