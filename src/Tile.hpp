#ifndef TILE_HPP
# define TILE_HPP
# include "../pch.hpp"

class Tile
{
public:
	Tile(const unsigned& gird_pos_x, const unsigned& gird_pos_y, const unsigned& tile_size, sf::Texture* texture_sheet, sf::IntRect texture_rect, bool damaging, float scale);
	~Tile();

	const sf::FloatRect getGlobalBounds() const;

	void update();
	void render(sf::RenderTarget& target);

private:
	sf::Sprite sprite;
	const bool damaging;


};

#endif
