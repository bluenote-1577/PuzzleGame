#ifndef BLOCKTREE_HPP
#define BLOCKTREE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Block.hpp"
#include "Includer.hpp"
#include "MainMenu.hpp"
#include <list>
#include <unordered_set>
#include <utility>
#include <cmath>
#include <iostream>
#include <fstream>



class Blocktree : public Block{


public:

	//members and constructor
	static	const int column_length = 10;
	Blocktree();
	int score;

	bool is_game_over();
	int combo_count;
	int last_score;
	//functions
	int clickOccur_swap(sf::RenderWindow& window,const sf::FloatRect& reset, const sf::FloatRect& menu, MainMenu& mainmenu );
	void drawTree(sf::RenderTarget& window, sf::RenderStates state);
	bool clickOccur_clear(sf::RenderWindow& window, const sf::FloatRect& reset, const sf::FloatRect& menu, MainMenu& mainmenu);
	void updateScan();
	void clearScan();
	void updateGame_blocks(sf::Time time);
	int swap_colours (int id1, int id2);
	void draw_select(int id1, int id2, sf::RenderWindow& window, sf::RenderStates state);
	void gameover_reset(sf:: RenderWindow& window, const sf::FloatRect& reset,const sf::FloatRect& menu, MainMenu& mainmenu);
	void updateGame_drop();
	void re_initialize();
	bool highScore_recorded;
	sf:: Clock timerClock;
	sf:: Clock drop_clock;
	


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
	//typedef <std::vector<columnholder>> column_vector;
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
	void dropRow();
	void initializeTree();
	void eraserow(int idmap_row);
	void erasecolumn(int idmap_column);
	void scancolumn();
	void scanrow();
	void setType(int id);
	void scancolumn_new();

	

	
}

;



#endif