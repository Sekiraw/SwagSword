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

	this->createHitboxComponent(this->sprite, 86.f, 76.f, 86.f, 96.f);
	this->createMovementComponent(300.f, 14.f, 8.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK", 10.f, 0, 1, 11, 1, 192, 192);
}

MyPlayer::~MyPlayer()
{
}

//Functions
void MyPlayer::update(const float& dt)
{
	
	this->movementComponent->update(dt);
	//258

	if (this->movementComponent->getState(IDLE)) 
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if(this->movementComponent->getState(MOVING_LEFT))
	{
		this->sprite.setOrigin(0, 0.f); //Flip
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("WALK", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT)) 
	{
		this->sprite.setOrigin(258.f, 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("WALK", dt);
	}
	else if (this->movementComponent->getState(MOVING_UP)) {
		this->animationComponent->play("WALK", dt);

	}
	else if (this->movementComponent->getState(MOVING_DOWN)) {
		this->animationComponent->play("WALK", dt);

	}

	this->hitboxComponent->update();
}
