#include"precom.h"
#include "GameState.h"
#include "test.h"

//Initializer functions

void GameState::initVariables()
{
	this->positionFileLocation = "Saves/PlayerPosition.ini";
}

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
		0,
		0,
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	));
}

void GameState::initView()
{
	this->view.setSize(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	));
	this->view.setCenter(sf::Vector2f(
		this->stateData->gfxSettings->resolution.width / 2.f, //Static cast float?
		this->stateData->gfxSettings->resolution.height / 2.f
	));
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");
	if (ifs.is_open()) {
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);

		}
	}
	ifs.close();
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 800.f, "Quit");
}

void GameState::initPlayers()
{
	myplayer = new MyPlayer(this->pPositionX, this->pPositionY, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap();
	TileMap::GetTileMap().InitializeTileMap(TileMap::GetTileMap().GetGridSize(), TileMap::GetTileMap().GetVectorX(), TileMap::GetTileMap().GetVectorY(), TileMap::GetTileMap().GetTextureFile());
	//this->stateData->gridSize, 10, 10, tileMap->texture_file
	//this->tileMap->loadFromFile("text.slmp");
}

//Get the player's starting position
void GameState::initPlayerPosition(std::string& file_name)
{
	this->pPositionX = 0;
	this->pPositionY = 0;

	std::ifstream in_file;
	in_file.open(file_name);
	if (in_file.is_open())
	{

		//Basics
		in_file >> this->pPositionX >> this->pPositionY;
		std::cout << "pos_x: " << this->pPositionX << "\n";
		std::cout << "pos_y: " << this->pPositionY << "\n";
	}
	else
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT LOAD PLAYER POSITION::FILENAME: " << file_name << "\n";
	}

	in_file.close();

}

//Constructors / Destructors
GameState::GameState(StateData* state_data)
	: State(state_data)
	, myplayer(nullptr)
{
	this->initVariables();
	this->initDeferredRender();
	this->initView();
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();

	this->initPlayerPosition(this->positionFileLocation);

	this->initPlayers();
	this->initTileMap();
}
GameState::~GameState() {
	delete this->pmenu;
	delete this->myplayer;
	delete this->tileMap;
}

//Functions
void GameState::updatePlayerStartingPosition(std::string& file_name)
{
	std::ofstream out_file;
	out_file.open(file_name);
	if (out_file.is_open())
	{
		out_file << myplayer->getPosition().x << " " << myplayer->getPosition().y;
	}
	else
	{
		std::cout << "ERROR::GAMESTATE::COULD NOT SAVE PLAYER POSITION::FILENAME: " << "Saves/PlayerPosition.ini" << "\n";
	}

	out_file.close();
}

void GameState::updateView(const float& dt)
{
	//Floor it for not messing up the blocks spaces ? idk its complicated
	this->view.setCenter(std::floor(this->myplayer->getPosition().x), std::floor(this->myplayer->getPosition().y));
}


void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime()) {
		if (!this->paused) {
			this->pauseState();
		}
		else {
			this->unpauseState();
		}
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
		this->myplayer->move(-1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
		this->myplayer->move(1.f, 0.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
		this->myplayer->move(0.f, -1.f, dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
		this->myplayer->move(0.f, 1.f, dt);
	}

	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		if (!this->paused) {
			this->pauseState();
		}
		else {
			this->unpauseState();
		}
	}*/
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
	{
		this->updatePlayerStartingPosition(this->positionFileLocation);
		this->endState();
	}
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->update();
	this->tileMap->updateCollision(this->myplayer);
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateKeyTime(dt);
	this->updateInput(dt);
	//this->getPlayerPosition();

	if (!this->paused) //Unpaused update
	{ 
		this->updateView(dt);
		this->updatePlayerInput(dt);

		this->myplayer->update(dt);

		this->updateTileMap(dt);
	}
	else //Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target) 
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture);

	this->myplayer->render(this->renderTexture);

	if (this->paused) {
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//FINAL RENDER
	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);

}
