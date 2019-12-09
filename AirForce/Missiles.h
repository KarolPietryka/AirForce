#pragma once
#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;
class Missiles : public Drawable
{
public:
	Missiles();
	virtual void moveMissiles() = 0;
	void collisionOccured();
	bool getCollisionStatus();
	~Missiles();
protected:
	RectangleShape missileShape;
	sf::Vector2f size;
	sf::Vector2f speed;
	bool collision;// flag that indicate if enemy plane was hit by missile;
	Texture *missileTexture = new sf::Texture;
};

class PlayerMissiles : public Missiles
{
public:
	PlayerMissiles();
	PlayerMissiles(float _playerPositionX, float _playerPositionY);
	RectangleShape getMissilesShape();
	void moveMissiles() override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	~PlayerMissiles();
private:
	


};

