#ifndef BLOCK_HPP
#define BLOCK_HPP
#include <SFML/Graphics.hpp>

class Block : public sf::Drawable, public sf::Transformable{
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