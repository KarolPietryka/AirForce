#pragma once
#include "Plane.h"
#include "RandGenerator.h"
#include <ctime>
class Formation
{
public:
	Formation();
	Formation(unsigned _formationLevel, unsigned _planeLevel, sf::Vector2f _windowSize, unsigned _speedIterator);
	void setFormationOneZeroSet(const bool * _p_formationLocal);
	void setEnemyPlanesVector();
	void setPositionOfEnemyPlane(EnemyPlane *_p_enemyPlane);
	vector<EnemyPlane *> &getEnemyPlanes();
	float setFirstPlanePosition();
	float getFormationLenght();
	void moveFormation(vector<EnemyPlane *> _enemyPlanesVector);
	sf::Vector2f getFormationPosition();
	RandGenerator generator;
	~Formation();
private:
	sf::Vector2f formationPosition;
	float formationLenght;
	unsigned formationLevel;
	unsigned planeLevel;
	unsigned currentNumOfPlanes;
	unsigned formationSize;
	unsigned gapBetweenPlanes;
	float nextPlanePositionX;
	float nextPlanePositionY;
	double formationColumnAndRowSize;
	float formationStartLocationX;
	sf::Vector2f windowSize;
	vector<bool> formationOneZeroSet;//need to drawing
	vector<EnemyPlane *> enemyPlanes;
	unsigned speedIncrementation; // speed incrementation
};

