#pragma once
#include <SFML/Graphics.hpp>

class Animations
{
public:
	Animations(sf::Texture* _texture, sf::Vector2u _imageCount, float _switchTime);
	Animations(sf::Texture* _texture, float _switchingTime);
	Animations();
	~Animations();

	void updatePlayerAnimation(int row, sf::Clock &_clock);
	bool getAnimationFinishedStatus();

	sf::IntRect uvRect;

	sf::Vector2u imageCount;
	sf::Vector2u currentImage;
protected:
	bool animationFinished;
	float totalTime;
	float switchTime;
};

class ExplosiveAnimations : public Animations
{
public:
	ExplosiveAnimations(sf::Texture* _texture, sf::Vector2u _imageCount, float _switchTime);
	void updateExplosionAnimation();
	~ExplosiveAnimations();
private:
	sf::Clock clockExplosionTime;//Every animation on explosion have his own clock 
};

class BackGroundAnimations: public Animations
{
public:
	BackGroundAnimations(sf::Texture* _texture, float _switchTime);
	void updateBackGroundAnimation(sf::Clock & _clock);
	~BackGroundAnimations();

};

