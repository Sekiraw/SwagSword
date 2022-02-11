#pragma once
#include "State.h"
#include"PauseMenu.h"
#include"TileMap.h"

class PauseMenu;
class Player;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
	public State
{
public:
	MyPlayer* myplayer;
	TileMap* tileMap;

	float pPositionX;
	float pPositionY;

private:
	sf::View view;
	sf::RenderTexture renderTexture;
	sf::Sprite renderSprite;

	sf::Font font;
	PauseMenu* pmenu;

	std::string positionFileLocation;

	

	//Initializer functions
	void initVariables();
	void initDeferredRender();
	void initView();
	void initFonts();
	void initKeybinds();
	void initTextures();
	void initPauseMenu();
	void initPlayers();
	void initTileMap();
	void initPlayerPosition(std::string& file_name);

public:
	GameState(StateData* state_data);
	virtual ~GameState();

	//Accessors
	//void getPlayerPosition();

	//Functions
	void updatePlayerStartingPosition(std::string& file_name);
	void updateView(const float& dt);
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void updateTileMap(const float& dt);
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

