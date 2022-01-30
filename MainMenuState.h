#pragma once
#include "GameState.h"
#include"SettingsState.h"
#include"EditorState.h"
#include "Gui.h"


class MainMenuState :
	public State
{
private:
	//Variables
	GraphicsSettings& gfxSettings;
	sf::Texture backgroundTexture;
	sf::RectangleShape background;
	sf::Font font;

	std::map<std::string, gui::Button*>buttons;

	//Functions
	void initVariables();
	void initBackground();
	void initFonts();
	void initKeybinds();
	void initButtons();

public:
	MainMenuState(sf::RenderWindow* window, GraphicsSettings& gfxSettings, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~MainMenuState();

	//Functions
	void updateInput(const float& dt);
	void updateButtons();
	void update(const float& dt);
	void renderButtons(sf::RenderTarget& target);
	void render(sf::RenderTarget* target = NULL);
};


