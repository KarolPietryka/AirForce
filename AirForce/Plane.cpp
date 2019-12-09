#include "stdafx.h"
#include "Plane.h"



Plane::Plane(){}
Plane::~Plane(){}

Player::Player() {}
Player::Player(float _windowSizeX, float _windowSizeY) : windowSizeX(_windowSizeX), windowSizeY(_windowSizeY)
{
	speed	= 8.0f;//sets player speed
	size	= 150.0f;
	fireSpeed = 0.4f;
	switchTimeOfAnimation = 0.9f;
	score = 0;

	playerStartLocationX = windowSizeX / 2;
	playerStartLocationY = windowSizeY - 100.0f;

	playerShape.setPosition(playerStartLocationX, playerStartLocationY);//sets start position
	playerShape.setSize(sf::Vector2f(size, size));
	playerShape.setOrigin((playerShape.getSize().x / 2), (playerShape.getSize().x / 2));

	sf::Image image;
	image.loadFromFile("img/Animation4.png");
	image.createMaskFromColor(sf::Color::White);

	playerTexture->loadFromImage(image);
	playerShape.setTexture(playerTexture);

	animations = new Animations(playerTexture, sf::Vector2u(3, 1), switchTimeOfAnimation);
}
Animations * Player::getAnimations()
{
	return animations;
}
bool Player::ableToMove(Directions _direction)
{
	bool ret = true;;
	switch (_direction)
	{
	case Directions::left :
		if (playerShape.getPosition().x - (playerShape.getSize().x) / 2 <= 0)
		{
			ret = false;
		}
		break;
	case Directions::up:
		if (playerShape.getPosition().y - (playerShape.getSize().y) / 2 <= 0)
		{
			ret = false;
		}
		break;
	case Directions::right:
		if (playerShape.getPosition().x + (playerShape.getSize().x) / 2 > windowSizeX)
		{
			ret = false;
		}
		break;
	case Directions::down:
		if (playerShape.getPosition().y + (playerShape.getSize().y) / 2 > windowSizeY)
		{
			ret = false;
		}
		break;
	}
	return ret;
}
void Player::movePlayer(sf::Clock &_clock)
{
	if (Keyboard::isKeyPressed(Keyboard::Key::A) && ableToMove(Directions::left))
	{
		playerShape.move(-speed, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::D) && ableToMove(Directions::right))
	{
		playerShape.move(speed, 0);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::W) && ableToMove(Directions::up))
	{
		playerShape.move(0, -speed);
	}
	if (Keyboard::isKeyPressed(Keyboard::Key::S) && ableToMove(Directions::down))
	{
		playerShape.move(0, speed);
	}
	getAnimations()->updatePlayerAnimation(0, _clock);
	IntRect rec = getAnimations()->uvRect;
	playerShape.setTextureRect(rec);
}
PlayerMissiles * Player::fire(sf::Clock & _playerFireSpeedClock)
{
	PlayerMissiles  * playerMissiles;
	if (Keyboard::isKeyPressed(Keyboard::Key::V) && _playerFireSpeedClock.getElapsedTime().asSeconds() >= fireSpeed)//if it elapsed enought time since last fired missile
	{
		_playerFireSpeedClock.restart();
		playerMissiles = new PlayerMissiles(playerShape.getPosition().x, playerShape.getPosition().y);
	}
	else
	{
		playerMissiles = new PlayerMissiles(-1, -1);
	}
	return playerMissiles;	
}
float Player::getFireSpeed()
{
	return fireSpeed;
}
void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(playerShape, states);
}
RectangleShape Player::getPlayerShape()
{
	return playerShape;
}
void Player::addPointsToScore()
{
	score += 253;
}
unsigned Player::getScore()
{
	return score;
}
Player::~Player(){}

EnemyPlane::EnemyPlane(unsigned _planeLevel, float _enemyPositionX, float _enemyPositionY, unsigned _speedIncrementation):
																									planeLevel(_planeLevel),
																									enemyPositionX(_enemyPositionX), 
																									enemyPositionY(_enemyPositionY)																		
{
	collision = false;
	switch (planeLevel)
	{
		case 0:
		{
		
			speed = 4.0f + _speedIncrementation;//sets speed
			size = 100.0f;
			fireSpeed = 0.1f;

			sf::Image image;
			image.loadFromFile("img/enemyPlane_lvl1.png");
			image.createMaskFromColor(sf::Color::White);

			enemyTexture->loadFromImage(image);
			enemyShape.setTexture(enemyTexture);
			break;
		}
		case 1:
		{
			speed = 6.0f + _speedIncrementation;//sets speed
			size = 100.0f;
			fireSpeed = 0.1f;

			sf::Image image;
			image.loadFromFile("img/enemyPlane_lvl2.png");
			image.createMaskFromColor(sf::Color::White);

			enemyTexture->loadFromImage(image);
			enemyShape.setTexture(enemyTexture);
			break;
		}
		case 2:
		{
			speed = 8.0f + _speedIncrementation;//sets speed
			size = 100.0f;
			fireSpeed = 0.1f;

			sf::Image image;
			image.loadFromFile("img/enemyPlane_lvl3.png");
			image.createMaskFromColor(sf::Color::White);

			enemyTexture->loadFromImage(image);
			enemyShape.setTexture(enemyTexture);
			break;
		}


		default:
		{
			cout << "Error Enemy plane type" << endl;
		}
	}
	enemyShape.setPosition(enemyPositionX, enemyPositionY);//sets start position
	enemyShape.setSize(sf::Vector2f(size, size));
	enemyShape.setOrigin((enemyShape.getSize().x / 2), (enemyShape.getSize().x / 2));
}
RectangleShape &EnemyPlane::getEnemyShape()
{
	return enemyShape;
}
void EnemyPlane::moveEnemy() 
{
	enemyShape.move(0, speed);
}
void EnemyPlane::draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(enemyShape, states);
}
void EnemyPlane::collisionOccurred()
{
	collision = true;
}
bool EnemyPlane::getCollisionStatus()
{
	return collision;
}
float EnemyPlane::getSpeed()
{
	return speed;
}
EnemyPlane::~EnemyPlane(){}