#include "stdafx.h"
#include "VisualEffect.h"


VisualEffect::VisualEffect()
{
}
void VisualEffect::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(effectShape, states);
}
VisualEffect::~VisualEffect()
{
}

Explosion::Explosion(sf::Vector2f _startPosition, float _size)//pisture is a Squere shape so we need only one dimension
{
	switchTimeOfAnimation = 0.1f;
	size = _size;

	visualEffectStartLocationX = _startPosition.x;
	visualEffectStartLocationY = _startPosition.y;

	effectShape.setPosition(visualEffectStartLocationX, visualEffectStartLocationY);//sets start possition
	effectShape.setSize(sf::Vector2f(size, size));
	effectShape.setOrigin((effectShape.getSize().x / 2), (effectShape.getSize().y / 2));

	sf::Image image;
	image.loadFromFile("img/explosion.png");
	image.createMaskFromColor(sf::Color::White);

	effectTexture->loadFromImage(image);
	effectShape.setTexture(effectTexture);

	animations = new ExplosiveAnimations(effectTexture, sf::Vector2u(5, 3), switchTimeOfAnimation);
}
void Explosion::upDateAnimation()
{
	getAnimations()->updateExplosionAnimation();
	IntRect rec = getAnimations()->uvRect;
	effectShape.setTextureRect(rec);
}
ExplosiveAnimations * Explosion::getAnimations()
{
	return animations;
}
Explosion::~Explosion() {}
