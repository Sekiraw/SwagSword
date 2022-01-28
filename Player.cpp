#include "Player.h"

//Initializer functions
void MyPlayer::initVariables()
{
	this->attacking = false;
}

void MyPlayer::initComponents()
{

}


//Constructors / Destructors
MyPlayer::MyPlayer(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 86.f, 70.f, 86.f, 111.f);
	this->createMovementComponent(350.f, 14.f, 8.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK", 6.f, 0, 1, 11, 1, 192, 192);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 13, 2, 192 * 2, 192);
}

MyPlayer::~MyPlayer()
{
}

//Functions
void MyPlayer::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		this->attacking = true;
	}
}

void MyPlayer::updateAnimation(const float& dt)
{
	

	//Animate and check for animation end
	if (this->attacking)
	{
		//Set origin depending on direction
		if (this->sprite.getScale().x > 0.f) { //Facing left
			this->sprite.setOrigin(96.f, 0.f);

		}
		else { //Facing right
			this->sprite.setOrigin(258.f + 96.f, 0.f);
		}

		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->attacking = false;

			if (this->sprite.getScale().x > 0.f) { //Facing left
				this->sprite.setOrigin(0.f, 0.f);
			}
			else { //Facing right
				this->sprite.setOrigin(258.f, 0.f);
			}
		}
	}

	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x < 0.f) {
			this->sprite.setOrigin(0, 0.f); //Flip
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f) {
			this->sprite.setOrigin(258.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP)) {
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	}
	else if (this->movementComponent->getState(MOVING_DOWN)) {
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

	}
}

void MyPlayer::update(const float& dt)
{
	
	this->movementComponent->update(dt);
	
	this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}
