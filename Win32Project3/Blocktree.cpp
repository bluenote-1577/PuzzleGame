#include "Blocktree.hpp"


Blocktree:: Blocktree() : Pink(), Green(), Teal(),matrix(3),column_ids(3)

{
	


	Pink.loadFromFile("Buttons/GJ_button_03.png");//pink
	Teal.loadFromFile("Buttons/GJ_button_02.png");//teal
	Green.loadFromFile("Buttons/GJ_button_01.png");//green
	Pink_select.loadFromFile("Buttons/GJ_button_03_select.png");
	Green_select.loadFromFile("Buttons/GJ_button_01_select.png");
	Teal_select.loadFromFile("Buttons/GJ_button_02_select.png");
	srand(time(NULL));

	initializeTree(Pink,Teal,Green, Pink_select, Teal_select, Green_select);
	

}

void Blocktree:: drawTree(sf::RenderTarget& window, sf::RenderStates state)
{

	for (col& bro : matrix){
		for(auto& dude : bro)
			(*dude).draw(window,state);
	}
}

void Blocktree::clickOccur_clear(sf::RenderWindow& window, const sf::FloatRect& reset)
{
	sf:: FloatRect bounds;
	sf::FloatRect gamebounds(240.0,0,120.0,400) ;
	//sf::FloatRect gamebounds(0,0,600,600);
	sf:: Vector2i initial = sf::Mouse::getPosition(window);
	sf:: Vector2f position = window.mapPixelToCoords(initial);

	int pos_x = position.x;
	int pos_y = position.y;

	if(gamebounds.contains(pos_x,pos_y)){
		

		for (col& bro : matrix)
			for (auto& dude : bro)
				{

			
			bounds = (*dude).blockSprite.getGlobalBounds();
			if (bounds.contains(pos_x,pos_y)){
				
				score = (*dude).id;
				int idcheck = (*dude).id; //blocks are id'd in a matrix accordingly:
										// 3 7 11
										// 2 6 10
										// 1 5 9 
										// 0 4 8     row 1

				
				int id_row = idcheck % column_length; //obtain row #
				int id_col = idcheck / column_length;; //obtain column #
				bool column = false;
				bool row = false;

				if (row_ids.find(idcheck) != row_ids.end())
				{
					row = true;
				}

				if(findid(id_col,idcheck))
				{
					column = true;
				}

			//	if (column==true && row== true)
			//	{
			//	}
				 if(row == true && sf::Keyboard::isKeyPressed(sf::Keyboard::R))
					eraserow(idcheck);

				 else if(column==true && sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
					erasecolumn(idcheck);
					}

				
				break;
			}

		}


	}


	if (reset.contains(pos_x,pos_y)){
		for(auto& bro : matrix)
			bro.clear();

		initializeTree(Pink,Teal,Green, Pink_select, Teal_select, Green_select);
		
	}
	
}


void Blocktree::updateScan()
{
	for(auto& columns : column_ids)
		columns.clear();
	row_ids.clear();
	scanrow();
	scancolumn();
}


void Blocktree:: initializeTree (const sf::Texture& Pink, const sf::Texture& Teal,
								 const sf::Texture& Green, const sf::Texture& Pink_select,
								 const sf::Texture& Teal_select, const sf::Texture& Green_select)
{

	

		
		


		for ( int i = 0; 21>i; i++)
		{
		int random = rand()%3;
		//int random = 1;
		// use above for testing
			
		if (random == 0){
			std::unique_ptr<Block> ptr(new Block(Pink, Pink_select));
		
			ptr->type = Type::Pink;
			ptr->id = i;;

		matrix[i/column_length].push_back(std::move(ptr));
		}

		if (random == 1){
			std::unique_ptr<Block> ptr(new Block(Teal, Teal_select));
			ptr->type = Type::Teal;
			ptr->id = i;
		matrix[i/column_length].push_back(std::move(ptr));
		}

		if (random == 2){
			std::unique_ptr<Block> ptr(new Block(Green, Green_select));
			ptr->type = Type::Green;
			ptr->id = i;
		matrix[i/column_length].push_back(std::move(ptr));
		}


		
		(*matrix[i/column_length][i%column_length]).setOrigin();
		}
	

	score = 0;
	colsize[0]=matrix[0].size(),colsize[1] =matrix[1].size(),colsize[2] = matrix[2].size(); 
	row_is_full[0] = true;
	row_is_full[1] = true;
	row_is_full[2] = true;
	row_is_full[3] = true;
	row_is_full[4] = true;
	row_is_full[5] = true;
	finished_updating = false;
	updateScan();

}

void Blocktree::eraserow(int id_dude){


	//score++;

	for(col::iterator it = matrix[0].erase(matrix[0].begin()+id_dude % column_length ); it !=matrix[0].end(); it++)
	{		
		(*it)->id--;
		(*it) -> id_dropped++;
	}
	for(col::iterator it = matrix[1].erase(matrix[1].begin()+id_dude % column_length); it !=matrix[1].end(); it++)
	{		
		(*it)->id--;
		(*it) -> id_dropped++;
	}
	for(col::iterator it = matrix[2].erase(matrix[2].begin()+id_dude % column_length); it !=matrix[2].end(); it++)
	{
		(*it)->id--;		
		(*it) -> id_dropped++;
	}

	//for(col& column : matrix)
	//	for(auto& block : column)
		//	(*block).id_dropped = 1;
					
	colsize[0]--,colsize[1]--,colsize[2]--;
	finished_updating = false;
	updateScan();


}

void Blocktree::erasecolumn(int block_id){

	//score++;

	int id_col = block_id /column_length;
	int id_row = block_id % column_length;
	int id_first;
	int id_second;
	auto it_first = column_ids[id_col].begin();
	auto it_last = column_ids[id_col].begin();


	for(auto it = column_ids[id_col].begin(); it != column_ids[id_col].end(); it++){
		if ((*matrix[id_col][id_row]).type == it->type){
			id_first = it->id;
			it_first = it;
			break;
		}
	}

	for(auto it = it_first; (it != column_ids[id_col].end()); it++){
		id_second = it->id;
	}



	int id_drop = (id_second - id_first + 1);
	

	for(auto it = matrix[id_col].erase(matrix[id_col].begin()+(id_first%column_length), matrix[id_col].begin()+(id_second%column_length)+1); it != matrix[id_col].end(); it++){
		(*it)->id -= id_drop ;
		(*it)->id_dropped = id_drop;
	}

	colsize[id_col] -= id_drop;
	updateScan();
}


void Blocktree:: scancolumn()
{
	int num_col = 3;

	for(int i = 0; i<num_col; i++)
	{
		int pinkid = -1;
		int pinkcount = 0;
		int pinkmax=0;
		int greenid = -1;
		int greencount = 0;
		int greenmax=0;
		int tealid = -1;
		int tealcount = 0;  
		int tealmax=0;

		for( int b = 0; b< matrix[i].size(); b++)
		{
			if ((*matrix[i][b]).type == Type::Pink){
				pinkcount++;	
				if (pinkid==-1)	pinkid = b+i*column_length;
				if (pinkcount > pinkmax) pinkmax = pinkcount;

				tealcount = 0;
				greencount = 0;
				if (tealmax >= 3);
				else tealid = -1;
				if (greenmax >= 3);
				else greenid = -1;
				
			}

			else if ((*matrix[i][b]).type == Type::Green){
				greencount++;
				if (greenid==-1)greenid = b+i*column_length;
				if (greencount > greenmax) greenmax = greencount;

				pinkcount = 0;
				tealcount = 0;
				if (tealmax >= 3);
				else tealid = -1;
				if (pinkmax >= 3);
				else pinkid = -1;
			}

			else if ((*matrix[i][b]).type == Type::Teal){
				tealcount++;
				if (tealid==-1)tealid = b+i*column_length;
				if (tealcount>tealmax) tealmax = tealcount;

				pinkcount = 0;
				greencount = 0;
				if (pinkmax >= 3);
				else pinkid = -1;
				if (greenmax >= 3);
				else greenid = -1;
			}

		}

		if (pinkmax >= 3)
		{
			for( int max = pinkmax+(pinkid%column_length); max + i*column_length > pinkid ; pinkid++){

				std::unique_ptr<columnholder> hold(new columnholder(pinkid,Type::Pink));
				bool isinside = false;
				for(auto it = column_ids[i].begin(); it != column_ids[i].end(); it++){
					if (it->id == hold->id){
						isinside = true;
						break;
					}
				}

				if (isinside != true)
					column_ids[i].push_back(std::move(*hold));
			}
			
		}

		 if (greenmax >= 3)
		{
			for( int max = greenmax+(greenid%column_length); max+i*column_length > (greenid) ; greenid++){

			std::unique_ptr<columnholder> hold(new columnholder(greenid,Type:: Green));
			bool isinside = false;
			for(auto it = column_ids[i].begin(); it != column_ids[i].end(); it++){
				if (it->id == hold->id){
					isinside = true;
					break;
				}
			}
				if (isinside != true)
				column_ids[i].push_back(std::move(*hold));
			}
		}
		 if(tealmax>= 3)
		{
			for( int max = tealmax+(tealid%column_length); max+i*column_length > (tealid) ; tealid++){

				std::unique_ptr<columnholder> hold(new columnholder(tealid,Type::Teal));
				bool isinside = false;
				for(auto it = column_ids[i].begin(); it != column_ids[i].end(); it++){
					if (it->id == hold->id){
						isinside = true;
						break;
					}
				}

				if (isinside != true)
					column_ids[i].push_back(std::move(*hold));
			}
		}
	}
		
}


	



void Blocktree:: scanrow()
{

		int fullrows;
		
		if (matrix[0].size() >= matrix[1].size())
		{
			if (matrix[1].size() > matrix[2].size())
				fullrows = matrix[2].size();
			else fullrows = matrix[1].size();
		}

		else
		
		{ 
			if (matrix[0].size() > matrix[2].size())
				fullrows = matrix[2].size();
			else fullrows = matrix[0].size();
		}

		
		for(int b = 0; b<fullrows ; b++)
			row_is_full[b] = true;
	
		for(int c = column_length; c>fullrows; c--)
			row_is_full[c-1] = false;
		
		for (int i = 0; i<column_length; i++){
		if (row_is_full[i] == true){
			if((*matrix[0][i]).type == (*matrix[1][i]).type && 
						(*matrix[1][i]).type == (*matrix[2][i]).type){
						if(row_ids.find((*matrix[0][i]).id) == row_ids.end())	row_ids.insert((*matrix[0][i]).id);
						if(row_ids.find((*matrix[1][i]).id) == row_ids.end())	row_ids.insert((*matrix[1][i]).id);
						if(row_ids.find((*matrix[2][i]).id) == row_ids.end())	row_ids.insert((*matrix[2][i]).id);
					
			}
		}
	}

}

bool Blocktree:: findid(int idcol, int idcheck)
{

	bool isinside = false;

	for(auto it = column_ids[idcol].begin(); it != column_ids[idcol].end(); it++)
	{
		if (idcheck == it->id){
			isinside = true;
			break;}


	}

	return isinside;


}

void Blocktree::  updateGame(sf:: Time time)

{
	if (finished_updating == true)
		return;

	for( auto& column : matrix)
		for ( auto& elements : column){

		if	((*elements).drop(time) >(*elements).id_dropped*40){
			
			(*elements).id_dropped = 0;
			}

		if((*elements).id_dropped == 0){
			(*elements).blockSprite.setPosition(0.0f,0.0f);
			(*elements).setOrigin();
			}
		}
}

int Blocktree:: clickOccur_swap(sf::RenderWindow& window,const sf::FloatRect& reset)
{


	sf:: FloatRect bounds;
	sf::FloatRect gamebounds(240.0,100.0,120.0,300.0) ;
	//sf::FloatRect gamebounds(0,0,600,600);
	sf:: Vector2i initial = sf::Mouse::getPosition(window);
	sf:: Vector2f position = window.mapPixelToCoords(initial);

	int pos_x = position.x;
	int pos_y = position.y;




	
	if (reset.contains(pos_x,pos_y)){
		for(auto& bro : matrix)
			bro.clear();

		initializeTree(Pink,Teal,Green, Pink_select, Teal_select, Green_select);
		return -1;
		
	}
	
	if (gamebounds.contains(pos_x,pos_y)){
		for (auto& columns : matrix)
			for ( auto& objects : columns){

				if ((*objects).blockSprite.getGlobalBounds().contains(pos_x,pos_y)){
					
					return (*objects).id;
				}


			}
	}

	return -1;

}

void Blocktree :: swap_colours(int id1, int id2)
{

	if(id1 == -1 || id2 == -1 )
		return;

	bool valid_move = false;

	if (id2 == id1 + 1)
		valid_move = true;

	if (id2 == id1 - 1)
		valid_move = true;

	if (id2 == id1 + column_length)
		valid_move = true;

	if (id2 == id1 - column_length)
		valid_move = true;


	if (valid_move == false)
		return;

	Type temp;

	temp = (*matrix[id1/column_length][id1%column_length]).type;

	(*matrix[id1/column_length][id1%column_length]).type = (*matrix[id2/column_length][id2%column_length]).type;
	(*matrix[id2/column_length][id2%column_length]).type = temp;

	setType(id1);
	setType(id2);

	updateScan();
	return;




}

void Blocktree:: setType(int id)
{

	if	((*matrix[id/column_length][id%column_length]).type ==  Type::Pink){
		(*matrix[id/column_length][id%column_length]).blockSprite.setTexture(Pink);
		(*matrix[id/column_length][id%column_length]).select_blockSprite.setTexture(Pink_select);
	}
	else if ((*matrix[id/column_length][id%column_length]).type ==  Type::Green){
		(*matrix[id/column_length][id%column_length]).blockSprite.setTexture(Green);
		(*matrix[id/column_length][id%column_length]).select_blockSprite.setTexture(Green_select);
	}

	else if ((*matrix[id/column_length][id%column_length]).type ==  Type::Teal){
		(*matrix[id/column_length][id%column_length]).blockSprite.setTexture(Teal);
		(*matrix[id/column_length][id%column_length]).select_blockSprite.setTexture(Teal_select);
	}

}

void Blocktree :: draw_select(int id1, int id2, sf::RenderWindow& window, sf:: RenderStates state)

{
	(*matrix[id1/column_length][id1%column_length]).draw_select(window, state);
	(*matrix[id2/column_length][id2%column_length]).draw_select(window, state);

}

