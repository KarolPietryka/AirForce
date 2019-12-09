#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Libretto.h"
#include "Collision.h"
#include "VisualEffect.h"
#include <vector>

using namespace std;
using namespace sf;

class Engine
{
public:
	Engine(float _windowSizeX, float _windowSizeY);
	~Engine();
	Player & getPlayer();
	void setTextureRecforPlayer(const IntRect & rectangle);
	void updatePlayer(sf::Clock & _clock);
	void playerFire(sf::Clock & _clock);
	void createFormation(sf::Clock &_clockFormationTime);
	bool isGameOver();
	bool isGameCompleted();
	void updateBestScore();
	int readBestScore();
	vector<PlayerMissiles *> getPlayerMissilesVector();

	void updateMissiles();
	void updateMissiles_OutOfWindow(sf::Vector2f _missilePosition, int &i);
	void updateMissiles_Collision(int &i);
	void updateFormation();
	void updadeFormation_Move(sf::Vector2f _enemyPosition, vector<EnemyPlane *> &_enemyPlanesVector, int &i, int &j);
	void updateFormation_OutOfWindow(vector<EnemyPlane *> &_enemyPlanesVector, int &i, int &j);
	void updateFormation_Collision(sf::Vector2f _enemyPosition, vector<EnemyPlane *> &_enemyPlanesVector, int &i, int &j);
	void updateCollision();
	//void updateBattleField();
	void updateBackGround(sf::Clock _clock);
	void updateVisualEffect();

	void drawBackGround(sf::RenderWindow &_window);
	void drawMissiles(sf::RenderWindow &_window);
	void drawPlayer(sf::RenderWindow &_window);
	void drawEnemyFormation(sf::RenderWindow & _window);
	void drawExplosion(sf::RenderWindow & _window);
	void drawGameOver(sf::RenderWindow & _window);
	void drawScore(sf::RenderWindow & _window);
	void drawBestScore(sf::RenderWindow & _window);

private:
	float	windowSizeX, windowSizeY;
	Collision collisionEngine;
	bool	gameOver;
	Player	player;
	Libretto libretto;
	int lastGeneratedFormation; //number of last generated Formation. Need to decide if game is over
	unsigned formationGeneratorSpeed;// time sinc generation of one formation to other. Used in drawFormation() method
	vector <Explosion *> explosionVector;
	vector<Formation *> formationAgenda;//flow of formations
	vector<Formation *> existingFormations;
	vector<PlayerMissiles *> playerMissilesVector;
	int delatedFormations;  //number of delated formations. Need to decide if game is over
	int bestScore;

	Texture *backGroundTexture = new sf::Texture;
	BackGroundAnimations *backGroundAnimations;
	RectangleShape backGroundShape;

	Texture *gameOverTexture = new sf::Texture;
	RectangleShape gameOverShape;

};

