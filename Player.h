#pragma once
#include "Entity.h"
class MyPlayer :
	public Entity
{
private:
	//Variables

	//Initializer functions
	void initVariables();
	void initComponents();
public:
	MyPlayer(float x, float y, sf::Texture& texture_sheet);
	virtual ~MyPlayer();

	//Functions
};

