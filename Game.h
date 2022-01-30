#pragma once
#include "MainMenuState.h"

class Game
{
private:
	//Variables
	GraphicsSettings gfxSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event e;

	sf::Clock dtClock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	float gridSize;

	//Initializations
	void initVariables();
	void initGraphicsSettings();
	void initWindow();
	void initStates();
	void initKeys();
	void initStateData();

public:
	//Constructors/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

