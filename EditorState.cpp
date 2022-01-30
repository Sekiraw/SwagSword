#include"precom.h"
#include "EditorState.h"

//Initializer functions
void EditorState::initVariables()
{
}

void EditorState::initBackground()
{
	
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Dosis-Light.ttf")) {
		throw("ERROR::EDITORSTATE::COULD NOT LOAD FONT");
	}
}

void EditorState::initKeybinds()
{

	std::ifstream ifs("Config/editorstate_keybinds.ini");
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
void EditorState::initPauseMenu()
{
	this->pmenu = new PauseMenu(*this->window, this->font);

	this->pmenu->addButton("QUIT", 800.f, "Quit");
}

void EditorState::initButtons()
{
	
}
EditorState::EditorState(StateData* state_data)
	: State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();

}
EditorState::~EditorState() {
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.end(); ++it) {
		delete it->second;
	}

	delete this->pmenu;
}


//Functions

void EditorState::updateInput(const float& dt)
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

void EditorState::updateButtons()
{
	/*
		Updates all the buttons in the state and handles their functionality.
	*/
	for (auto& it : this->buttons) {
		it.second->update(this->mousePosView);
	}

}

void EditorState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateKeyTime(dt);
	this->updateInput(dt);

	this->updateButtons();

	if (!this->paused) //Unpaused
	{
		this->updateButtons();
	}
	else //Paused
	{
		this->pmenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}


	//this->gamestate_btn->update(this->mousePosView);

	//Mouse position check
	/*system("cls");
	std::cout << this->mousePosView.x << " " << this->mousePosView.y << "\n";*/
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons) {
		it.second->render(target);
	}
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderButtons(*target);

	this->map.render(*target);

	if (this->paused) {
		this->pmenu->render(*target);
	}

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
