#ifndef BLOCKTREE_HPP
#define BLOCKTREE_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "Block.hpp"
#include "Includer.hpp"
#include <list>
#include <unordered_set>

class Blocktree : public Block{


public:

	Blocktree();
	void drawTree(sf::RenderTarget& window, sf::RenderStates state);
	int score;
	void clickOccur(sf::RenderWindow& window,sf::Text& text, const sf::FloatRect& reset);
	void updateScan();
	void clearScan();

private:

	typedef std::vector<Block> col;
	std::vector<col> matrix;
	sf:: Texture Pink;
	sf:: Texture Green;
	sf:: Texture Teal;

	bool row_is_full[4];
	int colsize[3];

	void initializeTree(const sf::Texture& colour1,const 
		sf::Texture& colour2,const sf::Texture& colour3);

	void eraserow(int idmap_row);
	void erasecolumn(int idmap_column);
	
	void scancolumn();
	void scanrow();
	std::unordered_set<int> column_ids;
	std::unordered_set<int> row_ids;



}

;



#endif