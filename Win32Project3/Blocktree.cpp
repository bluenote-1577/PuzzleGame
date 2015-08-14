#include "Blocktree.hpp"


Blocktree:: Blocktree() : Pink(), Green(), Teal(),matrix(3),column_ids(3)

{
	


	Pink.loadFromFile("Buttons/GJ_button_03.png");//pink
	Teal.loadFromFile("Buttons/GJ_button_02.png");//teal
	Green.loadFromFile("Buttons/GJ_button_01.png");//green
	srand(time(NULL));

	initializeTree(Pink,Teal,Green);
	

}

void Blocktree:: drawTree(sf::RenderTarget& window, sf::RenderStates state)
{

	for (col& bro : matrix){
		for(auto& dude : bro)
			(*dude).draw(window,state);
	}
}

void Blocktree::clickOccur(sf::RenderWindow& window, sf:: Text& text, const sf::FloatRect& reset)
{
	sf:: FloatRect bounds;
	//sf::FloatRect gamebounds(240.0,140.0,120.0,160.0) ;
	sf::FloatRect gamebounds(0,0,600,600);
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

				
				int id_row = idcheck % 4; //obtain row #
				int id_col = idcheck / 4; //obtain column #
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

				 if(column==true){
					erasecolumn(idcheck);
					}

				 if(row == true)
					eraserow(id_row);
				break;
			}

		}


	}


	if (reset.contains(pos_x,pos_y)){
		for(auto& bro : matrix)
			bro.clear();

		initializeTree(Pink,Teal,Green);
		
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
								 const sf::Texture& Green)
{

	

		
		


		for ( int i = 0; 12>i; i++)
		{
		int random = rand()%3;
		//int random = 1;
		// use above for testing
			
		if (random == 0){
			std::unique_ptr<Block> ptr(new Block(Pink));
		
			ptr->type = Type::Pink;
			ptr->id = i;;

		matrix[i/4].push_back(std::move(ptr));
		}

		if (random == 1){
			std::unique_ptr<Block> ptr(new Block(Teal));
			ptr->type = Type::Teal;
			ptr->id = i;
		matrix[i/4].push_back(std::move(ptr));
		}

		if (random == 2){
			std::unique_ptr<Block> ptr(new Block(Green));
			ptr->type = Type::Green;
			ptr->id = i;
		matrix[i/4].push_back(std::move(ptr));
		}


		
		(*matrix[i/4][i%4]).setOrigin();
		}
	

	score = 0;
	colsize[0]=matrix[0].size(),colsize[1] =matrix[1].size(),colsize[2] = matrix[2].size(); 
	row_is_full[0] = true;
	row_is_full[1] = true;
	row_is_full[2] = true;
	row_is_full[3] = true;
	updateScan();

}

void Blocktree::eraserow(int id_row){


	score++;

	for(col::iterator it = matrix[0].erase(matrix[0].begin()+id_row); it !=matrix[0].end(); it++)
	{		
		(*it)->id--;
	}
	for(col::iterator it = matrix[1].erase(matrix[1].begin()+id_row); it !=matrix[1].end(); it++)
	{		
		(*it)->id--;
	}
	for(col::iterator it = matrix[2].erase(matrix[2].begin()+id_row); it !=matrix[2].end(); it++)
	{
		(*it)->id--;			
	}

	for(col& column : matrix)
		for(auto& block : column)
			(*block).setOrigin();
					
	colsize[0]--,colsize[1]--,colsize[2]--;
	
	updateScan();


}

void Blocktree::erasecolumn(int block_id){

	score++;

	int id_col = block_id / 4;
	int id_row = block_id % 4;
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

	for(auto it = it_first; ((it->type != (*matrix[id_col][id_row]).type) || (next(it) != column_ids[id_col].end())); it++){
		it_last = it;
	}

	it_last++;

	id_second = it_last->id;

	score = id_second;

	for(auto it = matrix[id_col].erase(matrix[id_col].begin()+(id_first%4), matrix[id_col].begin()+(id_second%4)+1); it != matrix[id_col].end(); it++)
		(*it)->id -= (id_second - id_first + 1) ;

	for(auto it = matrix[id_col].begin(); it != matrix[id_col].end(); it++)
		(*it)->setOrigin();

	colsize[id_col] = id - (id_second - id_first) - 1 ;
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
				if (pinkid==-1)	pinkid = b+i*4;
				if (pinkcount > pinkmax) pinkmax = pinkcount;

				tealcount = 0;
				greencount = 0;
			}

			else if ((*matrix[i][b]).type == Type::Green){
				greencount++;
				if (greenid==-1)greenid = b+i*4;
				if (greencount > greenmax) greenmax = greencount;

				pinkcount = 0;
				tealcount = 0;
			}

			else if ((*matrix[i][b]).type == Type::Teal){
				tealcount++;
				if (tealid==-1)tealid = b+i*4;
				if (tealcount>tealmax) tealmax = tealcount;

				pinkcount = 0;
				greencount = 0;
			}

		}

		if (pinkmax >= 3)
		{
			for( int max = pinkmax+pinkid; max + i*4 > pinkid ; pinkid++){

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
			for( int max = greenmax+greenid; max+i*4 > (greenid) ; greenid++){

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
			for( int max = tealmax+tealid; max+i*4 > (tealid) ; tealid++){

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
	
		for(int c = 4; c>fullrows; c--)
			row_is_full[c-1] = false;
		
		for (int i = 0; i<4; i++){
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