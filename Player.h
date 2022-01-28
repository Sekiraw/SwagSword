#pragma once
#include "Entity.h"
class MyPlayer :
	public Entity
{
private:
	//Variables
	bool attacking;

	//Initializer functions
	void initVariables();
	void initComponents();
public:
	MyPlayer(float x, float y, sf::Texture& texture_sheet);
	virtual ~MyPlayer();

	//Functions
	void updateAttack();
	void updateAnimation(const float& dt);
	virtual void update(const float& dt);

};

