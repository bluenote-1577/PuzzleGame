#ifndef BLOCK_HPP
#define BLOCK_HPP
#include <SFML/Graphics.hpp>

/**
					The Block Class :

A class that represents each Block object in the game.

All members are public. 

Inherits from sf::Drawable which just has virtual function draw() that is overwritten.

Basically a class that holds 2 textures for rendering, an int id_dropped for movement,
an int id to determine where the block should be rendered(i.e. what position it is in) using the setOrigin() function,
and a Type that indicates which sprite it should be given.

the drop(sf::Time time) function is the function that moves the block when it's id_dropped is not 0. 

For instructions on how to play the game, execute the game and click on the instructions button.

**/

class Block : public sf::Drawable{
public:
	
	Block();
	Block(const sf::Texture &texture, const sf::Texture &texture1);
	virtual void draw(sf::RenderTarget& window,  sf::RenderStates state ) const;
	void draw_select(sf::RenderTarget& window, sf::RenderStates state) const;
	void setOrigin();
	sf:: Sprite blockSprite;
	sf:: Sprite select_blockSprite;
	enum Type{
		Pink,
		Green,
		Teal,
	};

	Type type;
	int id;
	float drop(sf::Time time);
	int id_dropped;
	static const int column_length = 10;

protected:
	

};

#endif