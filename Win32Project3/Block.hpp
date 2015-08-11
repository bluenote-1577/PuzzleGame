#ifndef BLOCK_HPP
#define BLOCK_HPP
#include <SFML/Graphics.hpp>
#include "Includer.hpp"

class Block : public sf::Drawable, public sf::Transformable{
public:
	
	Block();
	Block(const sf::Texture &texture);
	virtual void draw(sf::RenderTarget& window,  sf::RenderStates state ) const;
	void setOrigin(float x, float y);
	sf:: Sprite blockSprite;
	enum Type{
		Pink,
		Green,
		Teal,
	};

	Type type;
	int id;

protected:
	

};

#endif