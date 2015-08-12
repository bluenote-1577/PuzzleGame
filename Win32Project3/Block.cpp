#include "Block.hpp"


Block::Block()

{

}
Block :: Block(const sf::Texture& texture) : blockSprite(texture){

}

void Block:: draw(sf::RenderTarget& window,  sf::RenderStates state) const
{

	window.draw(blockSprite);

}

void Block:: setOrigin()
{

		float xpos = (float)(-240-40*(this->id/4));
		float ypos = (float)(-260+40*(this->id%4));
	blockSprite.setOrigin(xpos,ypos);



}