#include "Player.h"

//Initializer functions
void MyPlayer::initVariables()
{
}

void MyPlayer::initComponents()
{
	this->createMovementComponent(300.f, 15.f, 5.f);
}


//Constructors / Destructors
MyPlayer::MyPlayer(float x, float y, sf::Texture& texture)
{
	this->initVariables();
	this->initComponents();

	this->setTexture(texture);
	this->setPosition(x, y);
}

MyPlayer::~MyPlayer()
{
}
