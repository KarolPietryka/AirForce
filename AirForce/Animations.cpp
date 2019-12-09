#include "stdafx.h"
#include "Animations.h"


Animations::Animations(sf::Texture* _texture, sf::Vector2u _imageCount, float _switchTime)
{
	imageCount	= _imageCount;//[1,3]
	switchTime	= _switchTime;//0.7f
	animationFinished = false;
	totalTime	= 0.0f;
	currentImage.x = 0;

	uvRect.width	= (int)(_texture->getSize().x / (float)_imageCount.x);
	uvRect.height	= (int)(_texture->getSize().y / (float)_imageCount.y);
}
Animations::Animations() {}
Animations::Animations(sf::Texture* _texture, float _switchingTime)
{
	animationFinished = false;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = (int)_texture->getSize().x;
	uvRect.height = (int)_texture->getSize().y;
}
void Animations::updatePlayerAnimation(int _row, sf::Clock & _clock)
{
	//currentImage.y	= _row;
	totalTime		= _clock.getElapsedTime().asSeconds();

	if (totalTime >= switchTime)
	{
		_clock.restart();
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x && currentImage.y != imageCount.y - 1)
		{
			currentImage.x = 0;
			currentImage.y++;
		}
		else if (currentImage.x >= imageCount.x && currentImage.y == imageCount.y - 1)
		{
			currentImage.x = 0;
			currentImage.y = 0;
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top	= currentImage.y * uvRect.height;
}
bool Animations::getAnimationFinishedStatus()
{
	return animationFinished;
}
Animations::~Animations()
{
}
///////////////////////////////
ExplosiveAnimations::ExplosiveAnimations(sf::Texture* _texture, sf::Vector2u _imageCount, float _switchTime)
{
	imageCount = _imageCount;//[1,3]
	switchTime = _switchTime;//0.7f
	animationFinished = false;
	totalTime = 0.0f;
	currentImage.x = 0;

	uvRect.width = (int)(_texture->getSize().x / (float)_imageCount.x);
	uvRect.height = (int)(_texture->getSize().y / (float)_imageCount.y);
}
void ExplosiveAnimations::updateExplosionAnimation()
{
	totalTime = clockExplosionTime.getElapsedTime().asSeconds();

	if (totalTime >= switchTime)
	{
		clockExplosionTime.restart();
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= imageCount.x && currentImage.y != imageCount.y - 1)
		{
			currentImage.x = 0;
			currentImage.y++;
		}
		else if (currentImage.x >= imageCount.x && currentImage.y == imageCount.y - 1)
		{
			animationFinished = true;
		}
	}
	uvRect.left = currentImage.x * uvRect.width;
	uvRect.top = currentImage.y * uvRect.height;
}
ExplosiveAnimations::~ExplosiveAnimations(){}
///////////////////////////////
BackGroundAnimations::BackGroundAnimations(sf::Texture* _texture, float _switchTime)
{
	switchTime = _switchTime;
	animationFinished = false;
	totalTime = 0.0f;

	uvRect.width = (int)_texture->getSize().x;
	uvRect.height = (int)(_texture->getSize().y) / 3; //background is compilation of 3 pictures;
	
	uvRect.top = uvRect.height * 2;
}
void BackGroundAnimations::updateBackGroundAnimation(sf::Clock & _clock)
{
	totalTime = _clock.getElapsedTime().asSeconds();

	if (totalTime >= switchTime)
	{
		_clock.restart();
		totalTime -= switchTime;
		if (uvRect.top <= 0)
		{
			uvRect.top = uvRect.height * 2;//back to first picture (bottom one)
		}
		else
		{
			uvRect.top -= 0.7f;
		}	
	}
}
BackGroundAnimations::~BackGroundAnimations() {}
