#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Animations.h"
#include "Missiles.h"


using namespace std;
using namespace sf;

enum Directions
{
	left = 0,
	up = 1,
	right = 2,
	down = 3
};
/*enum EnemyPlanes
{
	level0 = 0,
	level1 = 1,
	level2 = 2,
	level3 = 3//TODO Fill with more types
};*/
class Plane : public Drawable
{
public:
	Plane();
	~Plane();
protected:
	float speed;
	float fireSpeed;
	float size;
};

class EnemyPlane : public Plane
{
public:
	EnemyPlane(unsigned _planeLevel, float _enemyPositionX, float _enemyPositionY, unsigned _speedIncrementation);
	~EnemyPlane();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	RectangleShape &getEnemyShape();
	void moveEnemy();
	void collisionOccurred();
	bool getCollisionStatus();
	float getSpeed();
private:
	bool collision;// flag that indicate if enemy plane was hit by missile;
	unsigned planeLevel;
	float enemyPositionX;
	float enemyPositionY;
	RectangleShape enemyShape;

	Texture *enemyTexture = new sf::Texture;
};
class Player : public Plane
{
public:
	Player();
	Player(float _windowSizeX, float _windowSizeY);
	~Player();
	void movePlayer(sf::Clock &_clock);
	PlayerMissiles  *fire(sf::Clock & _playerFireSpeedClock);
	float getFireSpeed();
	bool ableToMove(Directions _direction);
	Animations * getAnimations();
	RectangleShape getPlayerShape();
	void addPointsToScore();
	unsigned getScore();

private:
	float windowSizeX, windowSizeY;
	float playerStartLocationX;
	float playerStartLocationY;
	float switchTimeOfAnimation;
	Texture *playerTexture = new sf::Texture;
	Animations *animations;
	RectangleShape playerShape;
	unsigned score;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};

