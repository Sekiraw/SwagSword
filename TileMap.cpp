#include"precom.h"
#include "TileMap.h"

TileMap* TileMap::ms_pInstance;

void TileMap::SetDefaultTexture(std::string& texture)
{
	m_Config.texture_file = texture;
}

void TileMap::SetLayer(uint32_t layer)
{
	m_Config.layers = layer;
}

void TileMap::SetVectorX(uint32_t vx)
{
	m_Config.size.x = vx;
}

void TileMap::SetVectorY(uint32_t vy)
{
	m_Config.size.y = vy;
}

void TileMap::SetGridSize(float gs)
{
	m_Config.gridSize = gs;
}

__forceinline void TileMap::Clear()
{
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			for (size_t z = 0; z < m_Config.layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}

	this->map.clear();

	//std::cout << this->map.size() << "\n";
}

TileMap::TileMap()
{
	ms_pInstance = this;
	std::memset(&m_Config, 0, sizeof(TConfig));
}

bool TileMap::InitializeTileMap(float gridSize, uint32_t width, uint32_t height, std::string texture_file)
{
	this->gridSizeFl = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeFl);
	this->maxSizeWorldGrid.x = width;
	this->maxSizeWorldGrid.y = height;
	this->maxSizeWorldF.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorldF.y = static_cast<float>(height) * gridSize;
	m_Config.layers = 1;
	m_Config.texture_file = texture_file;

	this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<Tile*> >());
	for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
	{
		for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
		{
			this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());

			for (size_t z = 0; z < GetLayers(); z++)
			{
				this->map[x][y].resize(GetLayers(), NULL);
			}
		}
	}

	this->tileSheet.loadFromFile(texture_file);
	this->loadFromFile("Maps/text.slmp");

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineColor(sf::Color::Red);
	this->collisionBox.setOutlineThickness(1.f);

	return true;
}

TileMap::~TileMap()
{
	ms_pInstance = nullptr;
	Clear();
}

//Accessors
const sf::Texture* TileMap::getTileSheet() const
{
	return &tileSheet;
}

const sf::RectangleShape* TileMap::getCollisionBox() const
{
	return &collisionBox;
}

//Functions
void TileMap::saveToFile(const std::string file_name)
{
	/*
		Saves the entire tilemap to a text-file.
		Format:
		  Basic:
			Size x y
			gridSize
			layers
			texture file
			
		  All tiles:
			gridPos x y layer(z), Texture rect x y, collision, type

	*/

	std::ofstream out_file;
	out_file.open(file_name);
	if (out_file.is_open())
	{
		out_file << this->maxSizeWorldGrid.x << " " << this->maxSizeWorldGrid.y << "\n"
			<< this->gridSizeI << "\n"
			<< GetLayers() << "\n"
			<< this->textureFile << "\n";

		for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				for (size_t z = 0; z < GetLayers(); z++)
				{
					if(this->map[x][y][z])
						out_file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " "; //MAKE SURE THIS LAST SPACE IS NOT SAVED!
				}
			}
		}
		
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT SAVE TO FILE::FILENAME: " << file_name << "\n";
	}

	out_file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	/*
		Saves the entire tilemap to a text-file.
		Format:
		  Basic:
			Size x y
			gridSize
			layers
			texture file

		  All tiles:
			gridPos x y, Texture rect x y, collision, type

	*/

	std::ifstream in_file;
	in_file.open(file_name);
	if (in_file.is_open())
	{
		
		//Basics
		in_file >> m_Config.size.x >> m_Config.size.y >> m_Config.gridSize >> m_Config.layers >> textureFile;

		//Tiles
		/*std::cout << size.x << " x" << "\n";				- it gets the gridsize
		std::cout << size.y << " y" << "\n";
		std::cout << gridSize << " grid" << "\n";*/

		auto layer = GetLayers();

		gridSizeFl = m_Config.gridSize; // 0xC0000005: Access violation writing location 0x0000000000000008.
		gridSizeI = m_Config.gridSize;
		maxSizeWorldGrid.x = m_Config.size.x;
		maxSizeWorldGrid.y = m_Config.size.y;
		layer = m_Config.layers;
		//textureFile = m_Config.texture_file;
		SetDefaultTexture(textureFile);

		//this->clear();

		this->map.resize(this->maxSizeWorldGrid.x, std::vector<std::vector<Tile*> >());
		for (size_t x = 0; x < this->maxSizeWorldGrid.x; x++)
		{
			for (size_t y = 0; y < this->maxSizeWorldGrid.y; y++)
			{
				this->map[x].resize(this->maxSizeWorldGrid.y, std::vector<Tile*>());

				for (size_t z = 0; z < layer; z++)
				{
					this->map[x][y].resize(layer, NULL);
				}
			}
		}

		this->tileSheet.loadFromFile(GetTextureFile());

		//Load all tiles
		while (in_file >> m_Config.x >> m_Config.y >> m_Config.z >> m_Config.trX >> m_Config.trY >> m_Config.collision >> m_Config.type)
		{
			this->map[m_Config.x][m_Config.y][m_Config.z] = new Tile(
				m_Config.x, m_Config.y, gridSizeFl,
				this->tileSheet, sf::IntRect(m_Config.trX, m_Config.trY, this->gridSizeI, this->gridSizeI),
				m_Config.collision, m_Config.type
			);
		}
	}
	else
	{
		std::cout << "ERROR::TILEMAP::COULD NOT LOAD FROM FILE::FILENAME: " << file_name << "\n";
	}

	in_file.close();
}



void TileMap::addTile(const uint32_t x, const uint32_t y, const uint32_t z, const sf::IntRect& texture_rect, const bool& collision, const int16_t& type)
{
	/*
		Take two indicies from the mouse position in the grid and add a tile to that position if the internal tilemap array allows it.
	*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&  y < this->maxSizeWorldGrid.y && y >= 0 && z < GetLayers() && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			/*
				OK to add tile.
			*/

			this->map[x][y][z] = new Tile(x, y, this->gridSizeFl, this->tileSheet, texture_rect, collision, type);
			//std::cout << "Added valid tile" << "\n";
			
		}
		
	}

}

void TileMap::removeTile(const uint32_t x, const uint32_t y, const uint32_t z)
{
	/*
		Take three indicies from the mouse position in the grid and remove at that position if the internal tilemap array allows it.
	*/

	if (x < this->maxSizeWorldGrid.x && x >= 0 &&
		y < this->maxSizeWorldGrid.y && y >= 0 &&
		z < GetLayers() && z >= 0)
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

void TileMap::updateCollision(Entity* entity)
{
	//World Bounds
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
	}
	else if (entity->getPosition().x > this->maxSizeWorldF.x)
	{
		entity->setPosition(this->maxSizeWorldF.x, entity->getPosition().y);
	}
	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
	}
	else if (entity->getPosition().y > this->maxSizeWorldF.y)
	{
		entity->setPosition(this->maxSizeWorldF.x, this->maxSizeWorldF.y);
	}

	//Tiles
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto* z : y)
			{
				if (z != nullptr)
				{
					z->render(target);
					if (z->getCollision())
					{
						this->collisionBox.setPosition(z->getPosition());
						target.draw(this->collisionBox);
					}
				}	
			}
		}
	}
}

