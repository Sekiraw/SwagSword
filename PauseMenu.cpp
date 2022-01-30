#include"precom.h"
#include "PauseMenu.h"

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	: font(font)
{
	//Init background
	this->background.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x), 
		static_cast<float>(window.getSize().y)
	));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));
	
	//Init container
	this->container.setSize(sf::Vector2f(
		static_cast<float>(window.getSize().x) / 4.f,
		static_cast<float>(window.getSize().y) //To make the menu smaller just make for example y (this line) to y - 100...
	));
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 0); // ...and 30.f here

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(60);
	this->menuText.setString("PAUSED");
	this->menuText.setPosition(
		this->container.getPosition().x + this->container.getSize().x / 2.f - this->menuText.getGlobalBounds().width / 2.f, //center position
		this->container.getPosition().y + 40.f
	);
}

PauseMenu::~PauseMenu()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

std::map<std::string, gui::Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Functions
const bool PauseMenu::isButtonPressed(const std::string key) 
{
	return this->buttons[key]->isPressed();
}


void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 250.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f; //Center
	
	this->buttons[key] = new gui::Button(x, y, width, height, //x, y, width, height
		&this->font, text, 50,
		//Font
		sf::Color(200, 200, 200, 200),
		sf::Color(250, 250, 150, 250),
		sf::Color(20, 20, 20, 50),
		//Box
		sf::Color(100, 100, 100, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));
}

void PauseMenu::update(const sf::Vector2f& mousePos)
{
	for (auto &i : this->buttons) {
		i.second->update(mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons) {
		i.second->render(target);
	}

	target.draw(this->menuText);
}

