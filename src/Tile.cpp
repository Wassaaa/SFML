#include "Tile.hpp"

Tile::Tile(const unsigned& gird_pos_x, const unsigned& gird_pos_y, const unsigned& tile_size, sf::Texture *texture_sheet, sf::IntRect texture_rect,
	bool damaging, float scale) : damaging(damaging)
{
	this->sprite.setTexture(*texture_sheet);
	this->sprite.setTextureRect(texture_rect);
	this->sprite.setPosition(float(gird_pos_x * tile_size), float(gird_pos_y * tile_size));
	this->sprite.setScale(scale, scale);
}

Tile::~Tile()
{
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->sprite.getGlobalBounds();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget &target)
{
	target.draw(this->sprite);
}
