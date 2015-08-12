#include "Blocktree.hpp"


Blocktree:: Blocktree() : Pink(), Green(), Teal(),matrix(3,col(0))

{
	


	Pink.loadFromFile("Buttons/GJ_button_03.png");//pink
	Teal.loadFromFile("Buttons/GJ_button_02.png");//teal
	Green.loadFromFile("Buttons/GJ_button_01.png");//green
	srand(time(NULL));

	initializeTree(Pink,Teal,Green);


}

void Blocktree:: drawTree(sf::RenderTarget& window, sf::RenderStates state)
{

	for (col& dude : matrix){
		for(Block& bro : dude)
			bro.draw(window,state);
	}
}

void Blocktree::clickOccur(sf::RenderWindow& window, sf:: Text& text, const sf::FloatRect& reset)
{
	sf:: FloatRect bounds;
	sf::FloatRect gamebounds(240.0,140.0,120.0,160.0) ;
	sf:: Vector2i initial = sf::Mouse::getPosition(window);
	sf:: Vector2f position = window.mapPixelToCoords(initial);

	int pos_x = position.x;
	int pos_y = position.y;

	if(gamebounds.contains(pos_x,pos_y)){
		

		for (col bro : matrix)
			for (Block dude : bro)
				{

			
			bounds = dude.blockSprite.getGlobalBounds();
			if (bounds.contains(pos_x,pos_y)){
				
			//	score = dude.id;
				int idcheck = dude.id; //blocks are id'd in a matrix accordingly:
										// 3 7 11
										// 2 6 10
										// 1 5 9 
										// 0 4 8     row 1

				
				int id_row = idcheck % 4; //obtain row #
				int id_col = idcheck / 4; //obtain column #
				bool column = false;
				bool row = false;

				if (rowsize[id_row] >= 3){

					if(matrix[0][id_row].type == matrix[1][id_row].type && 
					matrix[1][id_row].type == matrix[2][id_row].type)
						row = true;
				}
				if(colsize[id_col] >= 3) {
					if (matrix[id_col][0].type == matrix[id_col][1].type &&
					matrix[id_col][1].type == matrix[id_col][2].type)
						column = true;
				}

			//	if (column==true && row== true)
			//	{
			//	}


				 if(row == true)
					eraserow(id_row);

				else if(row==true){
		
			
						score++;
					}

				
				break;
			}

		}


	}


	if (reset.contains(pos_x,pos_y)){
		for(auto& bro : matrix){
			bro.clear();}

		initializeTree(Pink,Teal,Green);
		
	}
	
}




void Blocktree:: initializeTree (const sf::Texture& Pink, const sf::Texture& Teal,
								 const sf::Texture& Green)
{

	

		
		


		for ( int i = 0; 12>i; i++)
		{
		int random = rand()%3;
		int random = 0;
		// use above for testing
			
		if (random == 0){
			std::unique_ptr<Block> ptr(new Block(Pink));
		
			ptr->type = Type::Pink;
			ptr->id = i;;
		matrix[i/4].push_back(std::move(*ptr));
		}

		if (random == 1){
			std::unique_ptr<Block> ptr(new Block(Teal));
			ptr->type = Type::Teal;
			ptr->id = i;
		matrix[i/4].push_back(std::move(*ptr));
		}

		if (random == 2){
			std::unique_ptr<Block> ptr(new Block(Green));
			ptr->type = Type::Green;
			ptr->id = i;
		matrix[i/4].push_back(std::move(*ptr));
		}


		
		matrix[i/4][i%4].setOrigin();
		}
	

	score = 0;
	colsize[0]=matrix[0].size(),colsize[1] =matrix[1].size(),colsize[2] = matrix[2].size(); 
	rowsize[0]=3,rowsize[1]=3,rowsize[2]=3;

}

void Blocktree::eraserow(int id_row){


	score++;

	for(col::iterator it = matrix[0].erase(matrix[0].begin()+id_row); it !=matrix[0].end(); it++)
	{		
		it->id--;
	}
	for(col::iterator it = matrix[1].erase(matrix[1].begin()+id_row); it !=matrix[1].end(); it++)
	{		
		it->id--;
	}
	for(col::iterator it = matrix[2].erase(matrix[2].begin()+id_row); it !=matrix[2].end(); it++)
	{
		it->id--;			
	}

	for(col& column : matrix)
		for(Block& block : column)
			block.setOrigin();
					
	colsize[0]--,colsize[1]--,colsize[2]--;




}

void Blocktree::erasecolumn(int id_row){

	score++;

}


std::set<int> Blocktree:: columnscan(int id_col)
{
	int array[] = {4,3,2,1};
	std::set<int> dude(array,array+5);
	return dude;
}