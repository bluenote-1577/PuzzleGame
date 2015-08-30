#include "MainMenu.hpp"

// Default constructor, initializes all the resources. Texts, strings, shapes have their positions and values initialized.

MainMenu :: MainMenu() : timedshape(sf::Vector2f(130,40)), instructions_shape(sf::Vector2f(130,40)), back(sf::Vector2f(50,50)),buttonColour(255,204,255,255),highscore_button(sf::Vector2f(130,40))
{
	
	main_font.loadFromFile("Buttons/ClaphappyLight.ttf");

	score_time = "Score					Time";
	actual_scores ="";
	actual_times = "";

	timedshape.setOrigin(-235,-150);
	timedshape.setOutlineColor(sf::Color::Black);
	timedshape.setOutlineThickness(2.0);
	timedshape.setFillColor(buttonColour);

	instructions_shape.setOrigin(-235,-220);
	instructions_shape.setOutlineColor(sf::Color::Black);
	instructions_shape.setOutlineThickness(2.0);
	instructions_shape.setFillColor(buttonColour);

	back.setOrigin(-500,-50);
	back.setOutlineColor(sf::Color::Black);
	back.setOutlineThickness(2.0);
	back.setFillColor(buttonColour);

	highscore_button.setOrigin(-235,-290);
	highscore_button.setOutlineColor(sf::Color::Black);
	highscore_button.setOutlineThickness(2.0);
	highscore_button.setFillColor(buttonColour);

	maintitle.setFont(main_font);
	maintitle.setPosition(200,20);
	maintitle.setColor(sf::Color::Black);
	maintitle.setString("Combo Puzzles!\n   By Jim Shaw");
	maintitle.setStyle(0);

	highscores_title.setFont(main_font);
	highscores_title.setPosition(200,20);
	highscores_title.setColor(sf::Color::Black);
	highscores_title.setString("High Scores");
	highscores_title.setStyle(0);

	highscores.setFont(main_font);
	highscores.setPosition(100,70);
	highscores.setColor(sf::Color::Black);
	highscores.setString(score_time);
	highscores.setStyle(0);

	hightimes.setFont(main_font);
	hightimes.setPosition(350,102);
	hightimes.setColor(sf::Color::Black);
	hightimes.setStyle(0);

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
	instructionsbutton.setPosition(235,220);
	instructionsbutton.setColor(sf::Color::Black);
	instructionsbutton.setString("Instructions");
	instructionsbutton.setStyle(0);

	instructions.setFont(main_font);
	instructions.setPosition(20,20);
	instructions.setCharacterSize(25);
	instructions.setColor(sf::Color::Black);
	instructions.setString("Welcome to ComboPuzzle! The goal of this\n game is to get as many points as possible\n of the same colour.\n You get points by clearing rows and columns of blocks\n that are greater than 3. To clear a row, hold the R key\n and left click a row that has 3 blocks. To clear a column \ndo the same but hold C instead. When you clear rows\n or columns, your combo counter increases. The higher it\n is, the more points you get!\n\n You can also swap blocks by clicking a block and dragging\n it to an adjacent block. However, when you swap, your\n combo counter resets to 0. Clear fast, or lose! \n\n");
	instructions.setStyle(0);
	
	highscores_text.setFont(main_font);
	highscores_text.setPosition(235,290);
	highscores_text.setColor(sf::Color::Black);
	highscores_text.setString("Highscores");
	highscores_text.setStyle(0);


	gamestatus = 0;

}

//Draws the correct resources depending on the gamestatus, i.e. which screen should be appearing.

void MainMenu:: drawScreen(sf::RenderWindow& window)
{
	if (gamestatus == 0){
		window.draw(timedshape);
		window.draw(maintitle);
		window.draw(instructions_shape);
		window.draw(instructionsbutton);
		window.draw(timedbutton);
		window.draw(highscore_button);
		window.draw(highscores_text);
	
	}

	if (gamestatus == 2){
		window.draw(instructions);
		window.draw(back);
		window.draw(reset);
	}

	if (gamestatus == 3){

		window.draw(back);
		window.draw(highscores);
		window.draw(reset);
		window.draw(highscores_title);
		window.draw(hightimes);


	}
	
}

// The click function in the GameLoop that allows us to switch between gamestatus or screens.
// when we click the highscores page, our function scanHighScores() scans the text file in the folder
//and returns the top 5 high scores and corresponding times into our containers.

void MainMenu :: clickOccur(sf::RenderWindow& window)
{
	sf:: Vector2i initial = sf::Mouse::getPosition(window);
	sf:: Vector2f position = window.mapPixelToCoords(initial);

	int pos_x = position.x;
	int pos_y = position.y;

	if(timedshape.getGlobalBounds().contains(pos_x,pos_y) && gamestatus ==0)
		gamestatus = 1;

	if(instructions_shape.getGlobalBounds().contains(pos_x,pos_y) && gamestatus == 0)
		gamestatus = 2;

	if(back.getGlobalBounds().contains(pos_x,pos_y) && (gamestatus == 2 || gamestatus == 3)){
		gamestatus = 0;
		score_container.clear();
		time_container.clear();
		actual_scores.clear();
		actual_times.clear();
	}
	if(highscore_button.getGlobalBounds().contains(pos_x,pos_y) && gamestatus == 0){
		scanHighScores();
		setHighScores();

		gamestatus = 3;

	}

}

//scans the text file and inputs our high scores.

bool MainMenu :: scanHighScores()
{

	std::ifstream myfile;
	myfile.open("high_scores.txt");
	std:: string first;
	std:: string second;
	std::string dicks = "1";



	if (myfile.fail())
		return false;

	while(myfile>> first >> second)
	{
		
		

		std::stringstream convert1(first);
		std::stringstream convert2(second);

		int score;
		int time;


		convert1 >> score;
		convert2 >> time;

		if(score < 0 || time < 0 || score > 59999 || time > 9999)
			return false;

		score_container.push_back(first);
		time_container.push_back(second);

	}

	myfile.close();
}

//actually writes the highscores into the strings. 

void MainMenu :: setHighScores()
{
	int i = 0;
	auto it2 = time_container.begin();
	for (auto it = score_container.begin(); i < 5 && it != score_container.end(); it++, i++){

		actual_scores += (*it);
		actual_scores += "\n";
		actual_times += (*it2);
		actual_times +="\n";


		it2++;
	}

	highscores.setString(score_time + "\n" + actual_scores);
	hightimes.setString(actual_times);
}