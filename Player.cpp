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

	this->createMovementComponent(300.f, 14.f, 8.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1, 11, 1, 192, 192);
}

MyPlayer::~MyPlayer()
{
}

//Functions
void MyPlayer::update(const float& dt)
{
	
	this->movementComponent->update(dt);

	if (this->movementComponent->idle()) 
	{
		this->animationComponent->play("IDLE_LEFT", dt);
	}
	else 
	{
		this->animationComponent->play("WALK_LEFT", dt);
	}
}
