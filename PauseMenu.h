#pragma once

#include "Gui.h"

#include<vector>
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>

#pragma comment( lib, "sfml-window-d.lib" )
#pragma comment( lib, "sfml-graphics-d.lib" )
#pragma comment( lib, "sfml-system-d.lib" )
#pragma comment( lib, "sfml-audio-d.lib" )
#pragma comment( lib, "sfml-network-d.lib" )
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"

class PauseMenu
{
private:
	sf::RectangleShape background;
	sf::RectangleShape container;

	sf::Font& font;
	sf::Text menuText;

	std::map<std::string, gui::Button*> buttons;

	//Private functions
	

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, gui::Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2f& mousePos);
	void render(sf::RenderTarget& target);
};

