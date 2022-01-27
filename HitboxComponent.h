#pragma once

#include<iostream>
#include<ctime>
#include<cstdlib>

#pragma comment( lib, "sfml-window-d.lib" )
#pragma comment( lib, "sfml-graphics-d.lib" )
#pragma comment( lib, "sfml-system-d.lib" )
#pragma comment( lib, "sfml-audio-d.lib" )
#pragma comment( lib, "sfml-network-d.lib" )
#include"SFML/Graphics.hpp"
#include"SFML/Window.hpp"
#include"SFML/System.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"
class HitboxComponent
{
private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	float offsetX, offsetY;

public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y,
		float width, float height);
	virtual ~HitboxComponent();

	//Functions
	bool checkIntersect(const sf::FloatRect& frect);

	void update();
	void render(sf::RenderTarget& target);
};

