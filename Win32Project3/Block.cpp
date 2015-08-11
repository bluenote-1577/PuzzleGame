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

void Block:: setOrigin(float x, float y)
{

	blockSprite.setOrigin(x,y);



}