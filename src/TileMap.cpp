#include "TileMap.hpp"

TileMap::TileMap()
{
	this->tileSheet = NULL;
	this->tileSize = 0;
}

TileMap::TileMap(unsigned width, unsigned height, sf::Texture *tile_sheet, unsigned tile_size)
{
	this->tileSheet = tile_sheet;
	this->tileSize = tile_size;
	width /= tile_size;
	height /= tile_size;

	this->tiles.resize(width);
	for (int i = 0; i < this->tiles.size(); i++)
		this->tiles[i].resize(height, nullptr);
}

TileMap::~TileMap()
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			delete this->tiles[i][j];
		}
	}

}

void TileMap::addTile(unsigned x, unsigned y, float scale, sf::IntRect rect)
{
	if (x < this->tiles.size() && x >= 0)
	{
		if (y < this->tiles[x].size() && y >= 0)
		{
			if (this->tiles[x][y] == nullptr)
			{
				this->tiles[x][y] = new Tile(x, y, this->tileSize, this->tileSheet, rect, false, scale);
			}
		}
	}
}

void TileMap::removeTile(unsigned x, unsigned y)
{
	if (x < this->tiles.size())
	{
		if (y < this->tiles[x].size())
		{
			if (this->tiles[x][y] != nullptr)
			{
				delete this->tiles[x][y];
				this->tiles[x][y] = nullptr;
			}
		}
	}
}

void TileMap::update()
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			if (this->tiles[i][j] != nullptr)
				this->tiles[i][j]->update();
		}
	}
}

void TileMap::render(sf::RenderTarget &target)
{
	for (int i = 0; i < this->tiles.size(); i++)
	{
		for (int j = 0; j < this->tiles[i].size(); j++)
		{
			if (this->tiles[i][j] != nullptr)
				this->tiles[i][j]->render(target);
		}
	}
}
