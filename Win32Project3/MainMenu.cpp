#include "MainMenu.hpp"

MainMenu :: MainMenu() : timedshape(sf::Vector2f(130,80)), instructions_shape(sf::Vector2f(130,80)), back(sf::Vector2f(50,50)),buttonColour(255,204,255,255)
{
	
	main_font.loadFromFile("Buttons/ClaphappyLight.ttf");

	timedshape.setOrigin(-235,-150);
	timedshape.setOutlineColor(sf::Color::Black);
	timedshape.setOutlineThickness(2.0);
	timedshape.setFillColor(buttonColour);

	instructions_shape.setOrigin(-235,-250);
	instructions_shape.setOutlineColor(sf::Color::Black);
	instructions_shape.setOutlineThickness(2.0);
	instructions_shape.setFillColor(buttonColour);

	back.setOrigin(-500,-50);
	back.setOutlineColor(sf::Color::Black);
	back.setOutlineThickness(2.0);
	back.setFillColor(buttonColour);

	maintitle.setFont(main_font);
	maintitle.setPosition(200,20);
	maintitle.setColor(sf::Color::Black);
	maintitle.setString("Combo Puzzles!\n   By Jim Shaw");
	maintitle.setStyle(0);

	reset.setFont(main_font);
	reset.setPosition(500,50);
	reset.setColor(sf::Color::Black);
	reset.setString("Back");
	reset.setStyle(0);
	reset.setCharacterSize(25);

	timedbutton.setFont(main_font);
	timedbutton.setPosition(235,150);
	timedbutton.setColor(sf::Color::Black);
	timedbutton.setString("Start");
	timedbutton.setStyle(0);

	instructionsbutton.setFont(main_font);
	instructionsbutton.setPosition(235,250);
	instructionsbutton.setColor(sf::Color::Black);
	instructionsbutton.setString("Instructions");
	instructionsbutton.setStyle(0);

	instructions.setFont(main_font);
	instructions.setPosition(20,20);
	instructions.setCharacterSize(25);
	instructions.setColor(sf::Color::Black);
	instructions.setString("Welcome to ComboPuzzle! The goal of this\n game is to get as many points as possible\n\n You get points by clearing rows and columns of blocks\n that are greater than 3. To clear a row, hold the R key\n and left click a row that has 3 blocks. To clear a column \ndo the same but hold C instead. When you clear rows\n or columns, your combo counter increases. The higher it\n is, the more points you get!\n\n You can also swap blocks by clicking a block and dragging\n it to an adjacent block. However, when you swap, your\n combo counter resets to 0. Clear fast, or lose! \n\n");
	instructions.setStyle(0);

	gamestatus = 0;

}


void MainMenu:: drawScreen(sf::RenderWindow& window)
{
	if (gamestatus == 0){
		window.draw(timedshape);
		window.draw(maintitle);
		window.draw(instructions_shape);
		window.draw(instructionsbutton);
		window.draw(timedbutton);
	}

	if (gamestatus == 2){
		window.draw(instructions);
		window.draw(back);
		window.draw(reset);
	}


	
}

void MainMenu :: drawInstructions(sf::RenderWindow& window)
{
	window.draw(instructions);
	window.draw(back);
}

void MainMenu :: clickOccur(sf::RenderWindow& window)
{
	sf:: Vector2i initial = sf::Mouse::getPosition(window);
	sf:: Vector2f position = window.mapPixelToCoords(initial);

	int pos_x = position.x;
	int pos_y = position.y;

	if(timedshape.getGlobalBounds().contains(pos_x,pos_y))
		gamestatus = 1;

	if(instructions_shape.getGlobalBounds().contains(pos_x,pos_y))
		gamestatus = 2;

	if(back.getGlobalBounds().contains(pos_x,pos_y))
		gamestatus = 0;


}