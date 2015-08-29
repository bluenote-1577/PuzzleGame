#ifndef BLOCKTREE_HPP
#define BLOCKTREE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Block.hpp"
#include "MainMenu.hpp"
#include <list>
#include <unordered_set>
#include <utility>
#include <cmath>
#include <iostream>
#include <fstream>

/**
					The Blocktree Class:

In summary : The class where all the game logic and gameplay happens. 

Inherits from Block class to make use of the enum Type, although in
hindsight that probably should've been an interface instead. Or the 
Block class should've been a friend. 



					Matrix Details :

Initiates a 10 x 3 vector matrix std::vector<col> matrix that holds all the blocks as pointers to blocks.
Blocks are ID'd  as following : 

.......
3 13 23
2 12 22				column 1 goes from 0 - 10, 4-10 omitted for succinctness
1 11 21	   <- row # 1
0 10 20    <- row # 0
   ^ column # 1
^
column # 0

ID's are absolute and will not move. Blocks can change ID's if they have to change positioning (i.e. blocks below them are removed, therefore they have to drop)
Blocks by column number and row number are ascertained by id/column_length for column number and id%column_length for row number. Accessing block 21
would be (*matrix[2][1]) (dereference since it's a POINTER to a block) or (*matrix[21/column_length][21%column_length].



					Erase Details :

The entire matrix is constantly scanned to see which id's are available for clearing. updateScan() is called every frame(loop) in updateGame_blocks.
There are two types of erase, a column erase and a row erase. Rows that are available for erasing(i.e. three same colours in a row) are scanned into an unordered_set row_ids and
when a block with an ID inside that set is clicked, every block in that row will be erased. A simplified structure, columnholder, is used to retain the ID and type of each block and
then stored into that container.

Scanning is similar for columns, but more complex. When there are three or more of the same colours consecutively, all of those ids will be scanned into a "package" vector(array)
that will be pushed back into a 2d vector(array). If a block is clicked on with id in that 3d vector, then the package vector's ids will be erased.

In summary : 

matrix ids -> mapped into column_ids,row_ids -> ids retrieved by erase function -> erase function erases ids from the matrix.



					Misc Details :

This class includes scoring, timers for dropping, combos, gameover functionality, and also the textures that the blocks
will be using.


**/
class Blocktree : public Block{


public:

	//members and constructor
	static	const int column_length = 10;
	Blocktree();
	int score;
	int combo_count;
	int last_score;
	bool highScore_recorded;
	sf:: Clock timerClock;
	sf:: Clock drop_clock;

	//functions
	int		 clickOccur_swap(sf::RenderWindow& window,const sf::FloatRect& reset, const sf::FloatRect& menu, MainMenu& mainmenu );
	void	 drawTree(sf::RenderTarget& window, sf::RenderStates state);
	bool	 clickOccur_clear(sf::RenderWindow& window, const sf::FloatRect& reset, const sf::FloatRect& menu, MainMenu& mainmenu);
	float	 updateGame_blocks(sf::Time time);
	int		 swap_colours (int id1, int id2);
	void	 draw_select(int id1, int id2, sf::RenderWindow& window, sf::RenderStates state);
	bool	 gameover_reset(sf:: RenderWindow& window, const sf::FloatRect& reset,const sf::FloatRect& menu, MainMenu& mainmenu);
	void	 re_initialize();
	bool	 is_game_over();

	


private:
	//private members
	struct columnholder{

		int id;
		Type type;
		columnholder()
		{
		}
		columnholder(int id, Type type){

			this->id = id;
			this->type = type;

		}
	};
	typedef std::vector<std::unique_ptr<Block>> col;
	std::vector<col> matrix;
	sf:: Texture Pink;
	sf:: Texture Green;
	sf:: Texture Teal;
	sf:: Texture Pink_select;
	sf:: Texture Green_select;
	sf:: Texture Teal_select;
	bool row_is_full[column_length];
	int colsize[3];
	std::vector <std::vector<std::vector<columnholder>>> column_ids;
	std::unordered_set<int> row_ids;
	bool findid(int idcol, int idcheck);
	bool finished_updating;
	bool game_over;
	int drops;



	//private functions
	void updateScan();
	void dropRow();
	void initializeTree();
	void eraserow(int idmap_row);
	void erasecolumn(int idmap_column);
	void scancolumn();
	void scanrow();
	void setType(int id);
	void scancolumn_new();
	float updateGame_drop();

	

	
}

;



#endif