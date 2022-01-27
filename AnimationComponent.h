#pragma once

#include<map>
#include<iostream>

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

class AnimationComponent
{
private:
	class Animation
	{
	public:
		//Variables
		sf::Sprite& sprite;
		sf::Texture& textureSheet;
		float animationTimer;
		float timer;
		int width;
		int height;
		sf::IntRect startRect;
		sf::IntRect currentRect;
		sf::IntRect endRect;

		Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, 
			float animationTimer, 
			int start_x, int start_y, int end_x, int end_y, int width, int height)
			: sprite(sprite), textureSheet(texture_sheet), 
			animationTimer(animationTimer), width(width), height(height)
		{
			this->startRect = sf::IntRect(start_x, start_y, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(end_x, end_y, width, height);

			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startRect);
		}

		//Functions
		void update(const float& dt) 
		{
			//Update timer
			this->timer = 10.f * dt;
			if (this->timer >= this->animationTimer)
			{
				//reset timer
				this->timer = 0.f;

				//Animate
				if (this->currentRect != this->endRect)
				{
					this->currentRect.left += this->width;
				}
				else //Reset
				{
					this->currentRect.left = this->startRect.left;
				}
			}
		}

		void pause();
		void reset();
	};

	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation> animations;

public:
	//Constructors / Destructors
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Functions
	void addAnimation(const std::string key);

	void startAnimation(const std::string animation);
	void pauseAnimation(const std::string animation);
	void resetAnimation(const std::string animation);


	void update(const float& dt);
};

