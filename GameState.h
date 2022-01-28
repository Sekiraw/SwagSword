#pragma once
#include "State.h"
#include"PauseMenu.h"

class GameState :
	public State
{
public:
	MyPlayer* myplayer;

private:
	sf::Font font;

	PauseMenu* pmenu;

	//Functions
	void initFonts();
	void initKeybinds();
	void initTextures();
	void initPauseMenu();
	void initPlayers();

public:
	GameState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~GameState();

	//Functions
	void updateInput(const float& dt);
	void updatePlayerInput(const float& dt);
	void updatePauseMenuButtons();
	void update(const float& dt);
	void render(sf::RenderTarget* target = NULL);
};

