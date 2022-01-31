#include"precom.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	
	this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*> >());
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, NULL);
			}
		}
	}

	this->tileTextureSheet.loadFromFile("Resources/Images/Tiles/tilesheet1.png");

}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}

//Functions

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& texture_rect)
{
	/*
		Take two indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it.
	*/

	if (x < this->maxSize.x && x >= 0 && 
		y < this->maxSize.y && y >= 0 && 
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			/*
				OK to add tile.
			*/

			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, this->tileTextureSheet, texture_rect);
			//std::cout << "Added valid tile" << "\n";
			
		}
		
	}

}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	/*
		Take three indicies from the mouse position in the grid and remove at that position if the internal tilemap array allows it.
	*/

	if (x < this->maxSize.x && x >= 0 &&
		y < this->maxSize.y && y >= 0 &&
		z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != nullptr)
		{
			/*
				OK to remove tile.
			*/

			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
			std::cout << "REMOVED TILE" << "\n";
		}

	}
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if(z != nullptr)
					z->render(target);
			}
		}
	}
}

