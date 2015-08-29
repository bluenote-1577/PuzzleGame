#include "Blocktree.hpp"

// Default constructor. Loads textures from folders to be accessed by new block objects and initializes all the blocks.

Blocktree:: Blocktree() : Pink(), Green(), Teal(),matrix(3),column_ids(3)

{
	


	Pink.loadFromFile("Buttons/GJ_button_03.png");//pink
	Teal.loadFromFile("Buttons/GJ_button_02.png");//teal
	Green.loadFromFile("Buttons/GJ_button_01.png");//green
	Pink_select.loadFromFile("Buttons/GJ_button_03_select.png");
	Green_select.loadFromFile("Buttons/GJ_button_01_select.png");
	Teal_select.loadFromFile("Buttons/GJ_button_02_select.png");
	srand(time(NULL));

	initializeTree();
	

}

// Renders the tree. Used everyframe in GameLoop. If game is over it renders the select sprite(lighter hue).

void Blocktree:: drawTree(sf::RenderTarget& window, sf::RenderStates state)
{
	if (game_over == false)
	{
	for (col& bro : matrix){
		for(auto& dude : bro)
			(*dude).draw(window,state);
	}
	}

	else{
		for (col& bro : matrix){
		for(auto& dude : bro)
			(*dude).draw_select(window,state);
		}
	}

}

//Click function used in GameLoop after a click has been detected whilst holding down the R or C key.
//Checks mouse position, maps it to global coordinates(detects resizing).
//Ascertains the block ID that is clicked on, and checks to see if the ID is valid for erasing by checking the ID mapping containers (column_ids, row_ids)
//Calls either the erasecolumn or eraserow function depending on which key is held and if erasing is valid.

//to note : if r or C are held and the upper left corner is clicked, a row drops. this was for testing purposes.

bool Blocktree::clickOccur_clear(sf::RenderWindow& window, const sf::FloatRect& reset, const sf::FloatRect& menu, MainMenu& mainmenu)
{

	if (game_over == true)
		return false;
	
	bool is_success = false;
	sf::FloatRect invisible_testing(0,0,50,50);
	sf:: FloatRect bounds;
	sf::FloatRect gamebounds(240.0,0,120,400) ;
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
				
				//score = (*dude).id;
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

	
				 if(row == true && sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
					eraserow(idcheck);
					is_success = true;
				 }

				 else if(column==true && sf::Keyboard::isKeyPressed(sf::Keyboard::C)){
					erasecolumn(idcheck);
					is_success = true;
					}

				
				break;
			}

		}

	return is_success;
	}



		if (invisible_testing.contains(pos_x,pos_y)){
		dropRow();
		return false;
	}

	
}

//Erase the ID mapping containers, and scans the entire blocktree and creates a new one. 

//Used in updateGame_blocks which is called
//every frame in the GameLoop.

void Blocktree::updateScan()
{
	for(auto& columns : column_ids)
		columns.clear();
	row_ids.clear();
	scanrow();
	scancolumn_new();
}

//Creates the std::vector<col> matrix. Creates a 3x5 matrix of random block colours, 
//and sets all the needed private member functions. Used when game resets, when Blocktree
///initializes.


void Blocktree:: initializeTree ()
{

	
	const int initialLength = 5;
		
		// id/column_length maps to the column number.
		// id%column_length maps to the row number.


		for ( int b = 0; 3>b; b++)
			for( int i = 0; initialLength>i; i++)
			{
			int random = rand()%3;
			//int random = 1;
			// use above for testing
			
			if (random == 0){
				std::unique_ptr<Block> ptr(new Block(Pink, Pink_select));
		
				ptr->type = Type::Pink;
				ptr->id = i + b*column_length;

			matrix[ptr->id/column_length].push_back(std::move(ptr));  
			}

			if (random == 1){
				std::unique_ptr<Block> ptr(new Block(Teal, Teal_select));
				ptr->type = Type::Teal;
				ptr->id = i + b*column_length;
			matrix[ptr->id/column_length].push_back(std::move(ptr));
			}

			if (random == 2){
				std::unique_ptr<Block> ptr(new Block(Green, Green_select));
				ptr->type = Type::Green;
				ptr->id = i+ b*column_length;
			matrix[ptr->id/column_length].push_back(std::move(ptr));
			}


		
			(*matrix[(i + b*column_length)/column_length][(i + b*column_length)%column_length]).setOrigin();
			}
	

	score = 0;
	colsize[0]=matrix[0].size(),colsize[1] =matrix[1].size(),colsize[2] = matrix[2].size(); 
	combo_count = 1;
	finished_updating = false;
	game_over = false;
	drops = 5;
	highScore_recorded = false;
	updateScan();
	drop_clock.restart();
	timerClock.restart();

	
}

//Called through clickOccur_clear function. If the id of the block was in the ID mapping container, then it calls this function
//Every block in the column above the block erased has id_dropped + 1 since it falls 1 block.

void Blocktree::eraserow(int id_dude){


	// id_dude is id passed, and id_dude%column_length describes which row number to erase.


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

					
	colsize[0]--,colsize[1]--,colsize[2]--;
	finished_updating = false;
	score+= 3 * combo_count;
	last_score = 3* combo_count;
	combo_count++;
	updateScan();


}

// A little more complicated erasecolumn function. Same method of calling as eraserow. the block_id is passed through the clickOccur_clear function again.


void Blocktree::erasecolumn(int block_id){

	int id_col = block_id /column_length;
	int id_row = block_id % column_length;
	int id_first;
	int id_second;
	auto it_first = column_ids[id_col][0].begin();
	auto it_last = column_ids[id_col][0].begin();
	int maxsize;
	int number_blocks_erased=0;

	// Scans the 3d vector(array) column_ids that has all the eraseable IDS mapped into it.
	// Uses the block id passed and checks to see which vector container it's in.
	// Breaks the nested for loop.

	for (auto& column : column_ids)
		for (auto & containers : column)
			for( auto it = containers.begin(); it != containers.end(); it++)
				if ((*matrix[id_col][id_row]).id == it->id){
					it_first = containers.begin();
					id_first = it_first->id;
				
					maxsize = containers.size();
					goto after;
				}

			

//Use iterators it_last and it_first to ascertain the correct Block ids.

after:
	it_last = it_first + maxsize - 1;
	id_second = it_last ->id;
	int id_drop = (id_second - id_first + 1);

//Checks how many blocks will be erased for scoring purposes, but more importantly if the
//blocks being erased and currently falling, the column will NOT erase.

	for(auto it = matrix[id_col].begin()+id_first%column_length; it != matrix[id_col].begin()+id_second%column_length+1; it++){
		number_blocks_erased++;
		if ((*it)->id_dropped != 0)
			return;
	}
//Erases id_first to id_second and moves id's and id_dropped accordingly.
	for(auto it = matrix[id_col].erase(matrix[id_col].begin()+(id_first%column_length), matrix[id_col].begin()+(id_second%column_length)+1); it != matrix[id_col].end(); it++){
		(*it)->id -= id_drop ;
		(*it)->id_dropped += id_drop;
	}

	colsize[id_col] -= id_drop;
	updateScan();
	score += number_blocks_erased * combo_count;
	last_score = number_blocks_erased * combo_count;
	combo_count++;
}


/**void Blocktree:: scancolumn()    

*************************************
The old scancolumn() function, the new one can handle the situation where the following occurs:

Teal
Teal
Teal
Green
Teal
Teal
Teal

I had to change the column ID mapping container into a 3d vector instead of a 2d one to deal with the situation
where 2 "packets" of eraseable blocks of the same colour occurs.

************************************

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


	
	**/

//scanrow() function, used to map eraseable (3 of the same colour) rows into 
//row_ids for erasing.

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

// scans a 3d array to see if an id is inside.
// used in clickOccur_clear to see if the id clicked is inside the id_columns container.
bool Blocktree:: findid(int idcol, int idcheck)
{

	bool isinside = false;

	for (auto& columns : column_ids)
			for(auto &containers : columns)
				for(auto it = containers.begin(); it!= containers.end(); it++)
					if (it->id ==idcheck )
						return true;
				
				
				
		


	

	return isinside;


}

//Update function called every frame in gameloop.
//calls updateScan for id containers, calls drop to drop blocks if the id_dropped is not 0;
// calls updateGame_drop to see if a row should be dropped,
// and returns the time left until a drop occurs.

float Blocktree::  updateGame_blocks(sf:: Time time)

{

	updateScan();
	float returnvalue = updateGame_drop();
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
	return returnvalue;

}

//The other click function called in the game loop. When R or C and not held, this function
//is called for swapping blocks and for going to the menu or restarting the game.
// all this function does is return the ID of the block so that the swap_colours function will work.

int Blocktree:: clickOccur_swap(sf::RenderWindow& window,const sf::FloatRect& reset, const sf::FloatRect& menu, MainMenu& mainmenu)
{

	if(game_over == true)
		return -1;

	sf:: FloatRect bounds;
	sf::FloatRect gamebounds(240.0,0.0,120.0,400) ;
	//sf::FloatRect gamebounds(0,0,600,600);
	sf:: Vector2i initial = sf::Mouse::getPosition(window);
	sf:: Vector2f position = window.mapPixelToCoords(initial);

	int pos_x = position.x;
	int pos_y = position.y;




	
	if (reset.contains(pos_x,pos_y)){
		re_initialize();
		return -2;
		
	}
	
	if (gamebounds.contains(pos_x,pos_y)){
		for (auto& columns : matrix)
			for ( auto& objects : columns){

				if ((*objects).blockSprite.getGlobalBounds().contains(pos_x,pos_y)){
					
					return (*objects).id;
				}


			}
	}

	if(menu.contains(pos_x,pos_y)){
		mainmenu.gamestatus = 0;
		re_initialize();
		return -1;
	}


	return -1;

}

// if the 2 ids are adjacent, colours are swapped. Combo resets.

int Blocktree :: swap_colours(int id1, int id2)
{

	if(id1 <0 || id2 < 0 )
		return -1;

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
		return 0;

	Type temp;

	temp = (*matrix[id1/column_length][id1%column_length]).type;

	(*matrix[id1/column_length][id1%column_length]).type = (*matrix[id2/column_length][id2%column_length]).type;
	(*matrix[id2/column_length][id2%column_length]).type = temp;

	setType(id1);
	setType(id2);

	combo_count = 1;

	updateScan();
	return 1;




}

//Used in swap_colours to change the actual textures depending on the type. Swap_colours just swaps the type, not the textures.

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

//used the in GameLoop to render the selected texture sprites (lighter hue) while swapping blocks.

void Blocktree :: draw_select(int id1, int id2, sf::RenderWindow& window, sf:: RenderStates state)

{
	(*matrix[id1/column_length][id1%column_length]).draw_select(window, state);
	(*matrix[id2/column_length][id2%column_length]).draw_select(window, state);

}

//Drops a row of blocks of random colour. If there are more than 10 blocks in a row and this function occurs, the game is over.
//arithmetic involving the use of column lengths and matrix stuff is used to ascertain the new block id and id_dropped.

void Blocktree :: dropRow()

{

	for(auto& columns : matrix){
		if (columns.size() >= column_length){
			game_over = true;
			return;
		}
	};
	
	
	for (int i = 0; i < 3; i++)
	{
		int random1 = rand()%3;
		if (random1 == 0){
			if (matrix[i].size() >= column_length) {game_over = true;}
			else{
				std::unique_ptr<Block> ptr(new Block(Pink, Pink_select));
				ptr->type = Type :: Pink;
				ptr-> id = (i+1)*column_length- 1;
				ptr-> id_dropped = column_length-matrix[i].size() - 1;
				ptr->setOrigin();
				ptr->id = ptr->id-column_length +1 +matrix[i].size();
				matrix[i].push_back(std::move(ptr));
			}
		}

		if (random1 == 1){
			if (matrix[i].size() >= column_length){game_over = true;}
			else{
				std::unique_ptr<Block> ptr(new Block(Green, Green_select));
				ptr->type = Type :: Green;
				ptr-> id = (i+1)*column_length- 1;
				ptr-> id_dropped = column_length -matrix[i].size() -1 ;
				ptr->setOrigin();
				ptr->id = ptr->id-column_length +1 +matrix[i].size();
				matrix[i].push_back(std::move(ptr));
			}
		}

		if (random1 == 2){
			if (matrix[i].size() >= column_length){game_over = true;}
			else{
				std::unique_ptr<Block> ptr(new Block(Teal, Teal_select));
				ptr->type = Type :: Teal;
				ptr-> id = (i+1)*column_length- 1;
				ptr-> id_dropped = column_length - matrix[i].size()- 1;
				ptr->setOrigin();
				ptr->id = ptr->id-column_length +1 +matrix[i].size();
					//id + matrix[i].size()-column_length + 1;
				matrix[i].push_back(std::move(ptr));
			}
		}

	}

	colsize[0]++;
	colsize[1]++;
	colsize[2]++;
	updateScan();
}

//if you've made it this far into my messy code then I don't think i need to explain what this function does

bool Blocktree:: is_game_over()
{


	if (game_over == true){


		return true;
	}
	else return false;


}

//this function is basically the reset portion of the clickOccur_swap function. this is called
//when the game is over and this is used instead of clickOccur_swap so the user can't swap blocks.

bool Blocktree:: gameover_reset(sf:: RenderWindow& window, const sf::FloatRect& reset,const sf::FloatRect& menu, MainMenu& mainmenu)
{

	sf:: Vector2i initial = sf::Mouse::getPosition(window);
	sf:: Vector2f position = window.mapPixelToCoords(initial);

	int pos_x = position.x;
	int pos_y = position.y;

	if(reset.contains(pos_x,pos_y)){

		re_initialize();

		game_over = false;
		return true;
		}

	if(menu.contains(pos_x,pos_y)){

		mainmenu.gamestatus = 0;
		re_initialize();
		game_over = false;
		return true;
	}

	else return false;

}

//drop timer function.
//This class has a drop_clock that continuously runs. When that drop_clock is equal to the timer,
//dropRow is called and the drop_clock resets. This timer is a function of the number of drops
//that has occured thus far. It is a reciprocal logarithmic function squared. The reason for this
//is that the difficulty of the game therefore increases really fast early on, but slows down later.

float Blocktree :: updateGame_drop()
{

	if(game_over == true)
		return 0.0;

	float time = drop_clock.getElapsedTime().asSeconds();
	float timer = (2/log10(drops)) * (2/log10(drops));

	if(timer > 4.1)
		timer = 9.0-0.5*drops;

	if(time/timer > 1){
	
	dropRow();
	drops++;
	drop_clock.restart();
	return 0.0;

	}

	if(timer-time < 0.1)
		return 0;

	else return (timer-time);
}

/**

The scancolumn_new() function:

This function scans the entire matrix and maps the ids that are available for clearing in a column(3 or more of the same colour into a packet then
into a 3d vector container. It can be thought about as a 2d vector container that holds another "packet" vector that contains all
the packets of blocks to be removed.  

**/

void Blocktree:: scancolumn_new()
{
	int num_col = 3;
	static const int maxOccur = (column_length/4); // this describes the maximum number of times "packets" of the same colour can occur in a row.

	for(int i = 0; i<num_col; i++)
	{
		int pinkid[maxOccur] = {-1,-1};		// pinkid = first id that appears  of the colour. pinkcount = current count of how many consecutive blocks of the same colour there are.
		int pinkcount = 0;					// pinkmax = the maximum number of consecutive blocks of the same colour. everything in an array of size 2 because you can have
		int pinkmax[maxOccur]= {0,0};		// 2 "packets" of pink, green or teal.
		int greenid[maxOccur] = {-1,-1};
		int greencount = 0;
		int greenmax[maxOccur]= {0,0};
		int tealid[maxOccur] = {-1,-1};
		int tealcount = 0;  
		int tealmax[maxOccur]= {0,0};
		int colour_occur[3] = {0,0,0}; // index 0 = pink, 1 = green, 2 = teal;

		//counter function. if 3 of the same type occurs consecutively, then it will be mapped into column_ids.

		for( int b = 0; b< matrix[i].size(); b++)
		{
			if ((*matrix[i][b]).type == Type::Pink && (*matrix[i][b]).id_dropped == 0){

				pinkcount++;	
				if (pinkid[colour_occur[0]]==-1) pinkid[colour_occur[0]] = b+i*column_length;
				if (pinkcount > pinkmax[colour_occur[0]]) pinkmax[colour_occur[0]] = pinkcount;
				
				if (tealmax[colour_occur[2]] >= 3){
					if(colour_occur[2] < (maxOccur-1))
						colour_occur[2]++;}
				else tealid[colour_occur[2]] = -1;
				if (greenmax[colour_occur[1]] >= 3 ){
					if(colour_occur[1] < (maxOccur-1))
						colour_occur[1]++;}
				else greenid[colour_occur[1]] = -1;

				tealcount = 0;
				greencount = 0;
				
			}

			else 
				if ((*matrix[i][b]).type == Type::Green && (*matrix[i][b]).id_dropped == 0){

				greencount++;	
				if (greenid[colour_occur[1]]==-1) greenid[colour_occur[1]] = b+i*column_length;
				if (greencount > greenmax[colour_occur[1]]) greenmax[colour_occur[1]] = greencount;
				
				if (tealmax[colour_occur[2]] >= 3 ){
					if(colour_occur[2] < (maxOccur-1))
						colour_occur[2]++;}
				else tealid[colour_occur[2]] = -1;
				if (pinkmax[colour_occur[0]] >= 3 ){
					if(colour_occur[0] < (maxOccur-1))
						colour_occur[0]++;}
				else pinkid[colour_occur[0]] = -1;

				tealcount = 0;
				pinkcount = 0;
			}

			else 
				if ((*matrix[i][b]).type == Type::Teal && (*matrix[i][b]).id_dropped == 0){
				tealcount++;	
				if (tealid[colour_occur[2]]==-1) tealid[colour_occur[2]] = b+i*column_length;
				if (tealcount > tealmax[colour_occur[2]]) tealmax[colour_occur[2]] = tealcount;
				

				
				if (pinkmax[colour_occur[0]] >= 3 ){
					if(colour_occur[0] < (maxOccur-1))
						colour_occur[0]++;}
				else pinkid[colour_occur[0]] = -1;
				if (greenmax[colour_occur[1]] >= 3 ){
					if(colour_occur[1] < (maxOccur-1))
						colour_occur[1]++;}
				else greenid[colour_occur[1]] = -1;

				pinkcount = 0;
				greencount = 0;

			}

		}

		//if max count is greater than 3, the starting id will be mapped into the column_id plus the maxcount.

			for( int c = 0; c<maxOccur; c++)
			{
			std::unique_ptr <std::vector<columnholder>> ptr_to_vector (new std::vector <columnholder>);

				if (pinkmax[c] < 3) break;
				for( int max = pinkmax[c]+(pinkid[c]%column_length); max + i*column_length > pinkid[c] ; pinkid[c]++){

					std::unique_ptr<columnholder> hold(new columnholder(pinkid[c],Type::Pink));
					bool isinside = false;
					

					if (isinside != true)
						(*ptr_to_vector).push_back(std::move(*hold));
				}


				column_ids[i].push_back(std::move(*ptr_to_vector));

			}
		
			for( int c = 0; c<maxOccur; c++)

			{
				std::unique_ptr <std::vector<columnholder>> ptr_to_vector (new std::vector <columnholder>);
				if (greenmax[c] < 3) break;
				for( int max = greenmax[c]+(greenid[c]%column_length); max + i*column_length > greenid[c] ; greenid[c]++){

					std::unique_ptr<columnholder> hold(new columnholder(greenid[c],Type::Green));
					bool isinside = false;
					

					if (isinside != true)
						(*ptr_to_vector).push_back(std::move(*hold));
				}
				column_ids[i].push_back(std::move(*ptr_to_vector));
			}
	
			for( int c = 0; c<maxOccur; c++)
			{
				std::unique_ptr <std::vector<columnholder>> ptr_to_vector (new std::vector <columnholder>);
				if (tealmax[c] < 3) break;
				for( int max = tealmax[c]+(tealid[c]%column_length); max + i*column_length > tealid[c] ; tealid[c]++){

					std::unique_ptr<columnholder> hold(new columnholder(tealid[c],Type::Teal));
					bool isinside = false;
					

					if (isinside != true)
						(*ptr_to_vector).push_back(std::move(*hold));
				}
			
				column_ids[i].push_back(std::move(*ptr_to_vector));
			}
	}
		
}

// intializes the tree again.

void Blocktree:: re_initialize()

{

	for(auto& bro : matrix)
			bro.clear();

		initializeTree();

}


