#include "Player.h"

//Initializer functions
void MyPlayer::initVariables()
{
}

void MyPlayer::initComponents()
{

}


//Constructors / Destructors
MyPlayer::MyPlayer(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 100.f, 0, 0, 13, 0, 195, 219);
}

MyPlayer::~MyPlayer()
{
}
