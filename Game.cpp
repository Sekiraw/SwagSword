#include"precom.h"
#include "Game.h"

//Static funcions

//Initializer functions
void Game::initVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	this->gridSize = 100.f;
}

void Game::initGraphicsSettings()
{
	this->gfxSettings.loadFromFile("Config/graphics.ini");
}

void Game::initWindow()
{
	/*
		Creates a SFML window.
	*/

	
	if (this->gfxSettings.fullscreen) {
		this->window = new sf::RenderWindow(this->gfxSettings.resolution, 
			this->gfxSettings.title,
			sf::Style::Fullscreen,
			this->gfxSettings.contextSettings);
	}
	else {
		this->window = new sf::RenderWindow(this->gfxSettings.resolution,
			this->gfxSettings.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->gfxSettings.contextSettings);
	}
	this->window->setFramerateLimit(this->gfxSettings.frameRateLimit);
	this->window->setVerticalSyncEnabled(this->gfxSettings.vSync);
}

void Game::initKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");
	if (ifs.is_open()) {
		std::string key = "";
		int key_value = 0;
		while (ifs >> key >> key_value)
		{
			this->supportedKeys[key] = key_value;

		}
	}
	ifs.close();

	//std::cout << this->supportedKeys.at("A") << "\n";

	//DEBUG REMOVE LATER
	for (auto i : this->supportedKeys) {
		std::cout << i.first << " " << i.second << "\n";
	}
}

void Game::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.gfxSettings = &this->gfxSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
	//this->states.push(new GameState(this->window, &this->supportedKeys));
}



//Constructors/Destructors
Game::Game() {
	this->initVariables();
	this->initGraphicsSettings();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}
Game::~Game() {
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}
//Functions
void Game::endApplication()
{
	std::cout << "Ending app" << "\n";
}
void Game::updateDt()
{
	/*
		Updates the dt variable with the time it takes to update and render one frame.
	*/
	this->dt = this->dtClock.restart().asSeconds();

}

void Game::updateSFMLEvents()
{
	while (this->window->pollEvent(this->e)) {
		if (this->e.type == sf::Event::Closed) {
			this->window->close();
		}
	}
}

void Game::update()
{
	this->updateSFMLEvents();

	if (!this->states.empty() && this->window->hasFocus())
	{
		this->states.top()->update(this->dt);

		if (this->states.top()->getQuit()) {
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
	//Application end
	else {
		endApplication();
		this->window->close();
	}
	

}

void Game::render()
{
	this->window->clear();

	if (!this->states.empty()) {
		this->states.top()->render(this->window);
	}

	//Render items
	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDt();
		this->update();
		this->render();
	}

}

