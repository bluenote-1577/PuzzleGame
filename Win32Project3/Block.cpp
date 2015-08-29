#include "Block.hpp"

// Default Constructor

Block::Block()

{
	
	id_dropped = 0;

}

//Constructor used in initializing block textures and id_dropped.

Block :: Block(const sf::Texture& texture, const sf::Texture& texture1) : blockSprite(texture), select_blockSprite(texture1){

	id_dropped = 0;

}

// public function used to render the normal blocksprite through Blocktree.drawTree

void Block:: draw(sf::RenderTarget& window,  sf::RenderStates state) const
{

	window.draw(blockSprite);

}

// public function used to render the selected blocksprite through Blocktree.drawTree. (selected blocksprite has a lighter hue)

void Block :: draw_select(sf::RenderTarget& window, sf::RenderStates state) const
{

	window.draw(select_blockSprite);

}

// sets the sprites' origins according to the block ID. used in updating block logic.
void Block:: setOrigin()
{

		float xpos = (float)(-240-40*(this->id/column_length));
		float ypos = (float)(-360+40*(this->id%column_length));
	blockSprite.setOrigin(xpos,ypos);
	select_blockSprite.setOrigin(xpos,ypos);



}

// checks to see if the block still has to fall. when id_dropped = 0, the block has stopped dropping. returns the total vertical movement of the block.
float Block:: drop(sf:: Time time)  

{
	if(this->id_dropped == 0)
		return 1;

	sf :: Vector2f movement (0.f,300.0f);
	blockSprite.move(time.asSeconds() * movement);

	return blockSprite.getPosition().y;



}

