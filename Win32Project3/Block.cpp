#include "Block.hpp"

Block::Block()

{
	id_dropped = 0;
}
Block :: Block(const sf::Texture& texture, const sf::Texture& texture1) : blockSprite(texture), select_blockSprite(texture1){

	id_dropped = 0;

	
}

void Block:: draw(sf::RenderTarget& window,  sf::RenderStates state) const
{

	window.draw(blockSprite);

}

void Block :: draw_select(sf::RenderTarget& window, sf::RenderStates state) const
{

	window.draw(select_blockSprite);

}

void Block:: setOrigin()
{

		float xpos = (float)(-240-40*(this->id/column_length));
		float ypos = (float)(-340+40*(this->id%column_length));
	blockSprite.setOrigin(xpos,ypos);
	select_blockSprite.setOrigin(xpos,ypos);



}

float Block:: drop(sf:: Time time)  //replaces    	//for(col& column : matrix)
										//	for(auto& block : column)
										//	(*block).setOrigin();
{
	if(this->id_dropped == 0)
		return 1;

	sf :: Vector2f movement (0.f,300.0f);
	blockSprite.move(time.asSeconds() * movement);

	return blockSprite.getPosition().y;



}

