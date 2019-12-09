#pragma once
#include <SFML\Graphics.hpp>
#include "Animations.h"

using namespace std;
using namespace sf;

class VisualEffect : public Drawable
{
public:
	VisualEffect();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~VisualEffect();
protected:
	ExplosiveAnimations *animations;
	Texture *effectTexture = new sf::Texture;
	RectangleShape effectShape;
	float switchTimeOfAnimation;
	float visualEffectStartLocationX;
	float visualEffectStartLocationY;
	float size;
};

class Explosion : public VisualEffect
{
public:
	Explosion(sf::Vector2f _startPosition, float _size);
	ExplosiveAnimations * getAnimations();
	void upDateAnimation();
	~Explosion();
private:
};

