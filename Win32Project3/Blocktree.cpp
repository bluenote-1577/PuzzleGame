#include "Blocktree.hpp"


Blocktree:: Blocktree() : Pink(), Green(), Teal(),matrix(3,row(0))

{
	


	Pink.loadFromFile("Buttons/GJ_button_03.png");//pink
	Teal.loadFromFile("Buttons/GJ_button_02.png");//teal
	Green.loadFromFile("Buttons/GJ_button_01.png");//green
	srand(time(NULL));

	for( int i = 0; 3>i; i++){

		float ypos = (float)(-180-i*40);
		


		for ( int b = 0; 3>b; b++)
		{
		int random = rand()%3;
		//int random = 0;
		// use above for testing
			
		if (random == 0){
			std::unique_ptr<Block> ptr(new Block(Pink));
		
			ptr->type = Type::Pink;
			ptr->id = ( b +i*3);
		matrix[i].push_back(std::move(*ptr));
		}

		if (random == 1){
			std::unique_ptr<Block> ptr(new Block(Teal));
			ptr->type = Type::Teal;
			ptr->id = ( b +i*3);
		matrix[i].push_back(std::move(*ptr));
		}

		if (random == 2){
			std::unique_ptr<Block> ptr(new Block(Green));
			ptr->type = Type::Green;
			ptr->id = ( b +i*3);
		matrix[i].push_back(std::move(*ptr));
		}


		float xpos = (float)(-240-b*40);
	

		matrix[i][b].setOrigin(xpos,ypos);
		}
	}

	score = 0;
	rowsize[0]=3,rowsize[1] =3,rowsize[2] = 3; 
	colsize[0]=3,colsize[1]=3,colsize[2]=3;
}

void Blocktree:: drawTree(sf::RenderTarget& window, sf::RenderStates state)
{

	for (row& dude : matrix){
		for(Block& bro : dude)
			bro.draw(window,state);
	}
}

void Blocktree::clickOccur(sf::RenderWindow& window, sf:: Text& text, const sf::FloatRect& reset)
{
	sf:: FloatRect bounds;
	sf::FloatRect gamebounds(240.0,180.0,120.0,120.0) ;
	sf:: Vector2i initial = sf::Mouse::getPosition(window);
	sf:: Vector2f position = window.mapPixelToCoords(initial);

	int pos_x = position.x;
	int pos_y = position.y;

	if(gamebounds.contains(pos_x,pos_y)){

		for (row bro : matrix)
			for (Block dude : bro)
				{

			bounds = dude.blockSprite.getGlobalBounds();
			if (bounds.contains(pos_x,pos_y)){
				
				int idcheck = dude.id; //blocks are id'd in a matrix accordingly:
										// 0 1 2
										// 3 4 5
										// 6 7 8

				
				int idmap1 = idcheck % 3; //obtain column #
				int idmap2 = idcheck / 3; //obtain row #
				bool column = false;
				bool row = false;


				if(matrix[0][idmap1].type == matrix[1][idmap1].type && 
				matrix[1][idmap1].type == matrix[2][idmap1].type)
					column = true;

				if(rowsize[idmap2] >= 3) {
					if (matrix[idmap2][0].type == matrix[idmap2][1].type &&
					matrix[idmap2][1].type == matrix[idmap2][2].type)
					row = true;
				}

				if(column == true){
					score++;

					for(row::iterator it = matrix[0].erase(matrix[0].begin()+idmap1); it !=matrix[0].end(); it++)
					{
					
							it->id--;
					}
					for(row::iterator it = matrix[1].erase(matrix[1].begin()+idmap1); it !=matrix[1].end(); it++)
					{
					
						
						it->id--;
					}
					for(row::iterator it = matrix[2].erase(matrix[2].begin()+idmap1); it !=matrix[2].end(); it++)
					{
						it->id--;
							
					}

					
					rowsize[0]--,rowsize[1]--,rowsize[2]--;



				}

				if(row==true){
		
			
					score++;
				}

				
				break;
			}

		}


	}


	if (reset.contains(pos_x,pos_y)){
		for(auto& bro : matrix){
			bro.clear();}

		for( int i = 0; 3>i; i++){

			float ypos = (float)(-180-i*40);
		


			for ( int b = 0; 3>b; b++){
				int random = rand() % 3;
				//int random = 0;
				// use above for testing
				if (random == 0){
					std::unique_ptr<Block> ptr(new Block(Pink));
					ptr->type = Type::Pink;
					ptr->id = ( b +i*3);
				matrix[i].push_back(std::move(*ptr));
				}

				if (random == 1){
					std::unique_ptr<Block> ptr(new Block(Teal));
					ptr->type = Type::Teal;
					ptr->id = ( b +i*3);
				matrix[i].push_back(std::move(*ptr));
				}

				if (random == 2){
					std::unique_ptr<Block> ptr(new Block(Green));
					ptr->type = Type::Green;
					ptr->id = ( b +i*3);
				matrix[i].push_back(std::move(*ptr));
				}


				float xpos = (float)(-240-b*40);
	

				matrix[i][b].setOrigin(xpos,ypos);
			}
		}
			rowsize[0]=3,rowsize[1]=3,rowsize[2] = 3; 
			colsize[0]=3,colsize[1]=3,colsize[2]=3;
	}
	
}



/**
void Blocktree:: initializeTree (const sf::Texture& Pink, const sf::Texture& Teal,
								 const sf::Texture& Green)
{

	for( int i = 0; 3>i; i++){

		float ypos = (float)(-180-i*40);
		


		for ( int b = 0; 3>b; b++)
		{
		int random = rand()%3;
		//int random = 0;
		// use above for testing
			
		if (random == 0){
			std::unique_ptr<Block> ptr(new Block(Pink));
		
			ptr->type = Type::Pink;
			ptr->id = ( b +i*3);
		matrix[i].push_back(std::move(*ptr));
		}

		if (random == 1){
			std::unique_ptr<Block> ptr(new Block(Teal));
			ptr->type = Type::Teal;
			ptr->id = ( b +i*3);
		matrix[i].push_back(std::move(*ptr));
		}

		if (random == 2){
			std::unique_ptr<Block> ptr(new Block(Green));
			ptr->type = Type::Green;
			ptr->id = ( b +i*3);
		matrix[i].push_back(std::move(*ptr));
		}


		float xpos = (float)(-240-b*40);
	

		matrix[i][b].setOrigin(xpos,ypos);
		}
	}

	score = 0;
	rowsize[0]=3,rowsize[1] =3,rowsize[2] = 3; 
	colsize[0]=3,colsize[1]=3,colsize[2]=3;

}
**/