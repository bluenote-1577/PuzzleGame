#ifndef BLOCKTREE_HPP
#define BLOCKTREE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Block.hpp"
#include "Includer.hpp"
#include <list>
#include <unordered_set>
#include <utility>

class Blocktree : public Block{


public:

	Blocktree();
	void drawTree(sf::RenderTarget& window, sf::RenderStates state);
	int score;
	void clickOccur_clear(sf::RenderWindow& window, const sf::FloatRect& reset);
	void updateScan();
	void clearScan();
	int clickOccur_swap(sf::RenderWindow& window,const sf::FloatRect& reset);
	void updateGame(sf::Time time);
	static	const int column_length = 7;
	void swap_colours (int id1, int id2);
	void draw_select(int id1, int id2, sf::RenderWindow& window, sf::RenderStates state);


private:

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

	typedef std::vector<columnholder> column_vector;
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

	void initializeTree(const sf::Texture& colour1,const 
		sf::Texture& colour2,const sf::Texture& colour3,
		const sf::Texture& colour1_select, const sf::Texture& colour2_select,
		const sf::Texture& colour3_select);

	void eraserow(int idmap_row);
	void erasecolumn(int idmap_column);
	
	void scancolumn();
	void scanrow();
	std::vector <std::vector<columnholder>> column_ids;
	std::unordered_set<int> row_ids;

	bool findid(int idcol, int idcheck);

	bool finished_updating;
	void setType(int id);
}

;



#endif