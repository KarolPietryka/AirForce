#include "stdafx.h"
#include "Missiles.h"


Missiles::Missiles()
{
	collision = false;
}
void Missiles::collisionOccured()
{
	collision = true;
}
bool Missiles::getCollisionStatus()
{
	return collision;
}
Missiles::~Missiles()
{
}

PlayerMissiles::PlayerMissiles() {}
PlayerMissiles::PlayerMissiles(float _playerPositionX, float _playerPositionY)
{
	if (_playerPositionX != -1)// solution for player.fire() method if fire button is no push
	{
		size.x = 70;
		size.y = 60;
		speed = { 0,0. - 4.0f };

		missileShape.setPosition(_playerPositionX, _playerPositionY);
		missileShape.setSize(size);
		missileShape.setOrigin((missileShape.getSize().x / 2), (missileShape.getSize().y / 2));

		sf::Image image;
		image.loadFromFile("img/2xPlayerMissile.png");
		image.createMaskFromColor(sf::Color::White);

		missileTexture->loadFromImage(image);
		missileShape.setTexture(missileTexture);
	}
	else
	{
		missileShape.setPosition(_playerPositionX, _playerPositionY);
	}
}
void PlayerMissiles::moveMissiles() 
{
	missileShape.move(0, speed.y);
}
RectangleShape PlayerMissiles::getMissilesShape()
{
	return missileShape;
}
void PlayerMissiles::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(missileShape, states);
}
PlayerMissiles::~PlayerMissiles() {}