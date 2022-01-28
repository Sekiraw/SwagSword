#include "SettingsState.h"

//Initializer functions
void SettingsState::initVariables()
{
}

void SettingsState::initBackground()
{
	this->background.setSize(sf::Vector2f
	(
		static_cast<float>(this->window->getSize().x),
		static_cast<float>(this->window->getSize().y)
	)
	);

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/backg.png")) {
		throw"ERROR::MAINMENUSTATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}
	this->background.setTexture(&this->backgroundTexture);
}

void SettingsState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingsState::initKeybinds()
{

	std::ifstream ifs("Config/mainmenustate_keybinds.ini");
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
void SettingsState::initButtons()
{

	this->buttons["EXIT"] = new Button(835.f, 575.f, 250.f, 50.f,
		&this->font, "Quit", 50,
		//Font
		sf::Color(100, 100, 100, 200),
		sf::Color(250, 250, 150, 250),
		sf::Color(20, 20, 20, 50),
		//Box
		sf::Color(100, 100, 100, 0),
		sf::Color(150, 150, 150, 0),
		sf::Color(20, 20, 20, 0));
}

SettingsState::SettingsState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	: State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();

}

SettingsState::~SettingsState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}
}

//Accessors

//Functions
void SettingsState::updateInput(const float& dt)
{


}

void SettingsState::updateButtons()
{
	/*
		Updates all the buttons in the state and handles their functionality.
	*/
	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}

	//Quit the game
	if (this->buttons["EXIT"]->isPressed()) {
		this->endState();
	}

}

void SettingsState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();




	//this->gamestate_btn->update(this->mousePosView);

	//Mouse position check
	/*system("cls");
	std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";*/
}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButtons(*target);

	//REMOVE LATER!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x + 20, this->mousePosView.y + 20);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(12);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y << "";
	mouseText.setString(ss.str());

	target->draw(mouseText);
}
