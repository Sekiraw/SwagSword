#pragma once
#include "Tile.h"
#include <cassert>
#include "Entity.h"

class TileMap
{
public:
	// Msvcp workaround
	TileMap();
	~TileMap();
	TileMap(const TileMap& other) = delete;
	TileMap(TileMap&& other) {}
	TileMap& operator = (const TileMap& other) = delete;
	TileMap& operator = (TileMap&& other)
	{
		if (this == &other)
			return *this;
		m_Config = std::move(other.m_Config);
		return *this;
	}

	// Instance
	static TileMap& GetTileMap() { assert(ms_pInstance != nullptr); return *ms_pInstance; }
	static TileMap* ms_pInstance;

	// Cfg
	typedef struct SConfig
	{
		std::string texture_file;
		sf::Vector2u size;
		

		float gridSize;
		uint32_t layers;
		uint32_t x;
		uint32_t y;
		uint32_t z;
		uint32_t trX;
		uint32_t trY;
		bool collision;
		int16_t type;
	} TConfig;

	// Main fnc
	__forceinline void DefaultValues();
	bool InitializeTileMap(float gridSize, uint32_t width, uint32_t height, std::string texture_file);
	__forceinline void Clear();

	//Accessors
	const sf::Texture* getTileSheet() const;
	const sf::RectangleShape* getCollisionBox() const;

	//Functions
	void addTile(const uint32_t x, const uint32_t y, const uint32_t z, const sf::IntRect& texture_rect, const bool& collision, const int16_t& type);
	void removeTile(const uint32_t x, const uint32_t y, const uint32_t z);
	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity);

	void update();
	void render(sf::RenderTarget& target, Entity* entity = nullptr);

	// Callback
	std::string GetTextureFile() const
	{
		return m_Config.texture_file;
	}

	uint32_t GetVectorX() const
	{
		return m_Config.size.x;
	}

	uint32_t GetVectorY() const
	{
		return m_Config.size.y;
	}

	float GetGridSize() const
	{
		return m_Config.gridSize;
	}

	uint32_t GetLayers() const
	{
		return m_Config.layers;
	}


	// Run Event

	void SetDefaultTexture(std::string& texture);
	void SetLayer(uint32_t layer);
	void SetVectorX(uint32_t vx);
	void SetVectorY(uint32_t vy);
	void SetGridSize(float gs);

public:
	float gridSizeFl = 0.f;
	int gridSizeI = 0;
	sf::Vector2u maxSizeWorldGrid;
	sf::Vector2f maxSizeWorldF;
	//unsigned layers;
	std::vector<std::vector<std::vector< Tile* > > > map;
	sf::Texture tileSheet;
	sf::RectangleShape collisionBox;

	// File Content
	std::string textureFile = "";
	float gridSize = 0.0f;
	uint32_t layer = 0;
	sf::Vector2u size;


protected: 
	TConfig m_Config;
};
