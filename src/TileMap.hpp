#ifndef TILEMAP_HPP
# define TILEMAP_HPP
# include "../pch.hpp"
# include "Tile.hpp"

class TileMap
{
public:
	TileMap();
	TileMap(unsigned widht, unsigned height, sf::Texture* tile_sheet, unsigned tile_size);
	~TileMap();

	//inline functions
	inline const unsigned& getTileSize() const { return this->tileSize;}

	//functions
	void addTile(unsigned x, unsigned y, float scale, sf::IntRect rect);
	void removeTile(unsigned x, unsigned y);

	void update();
	void render(sf::RenderTarget& target);

private:
	std::vector<std::vector<Tile*>> tiles;
	sf::Texture* tileSheet;
	unsigned tileSize;

};

#endif
