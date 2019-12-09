#include "stdafx.h"
#include "Collision.h"


Collision::Collision() {}

void Collision::updateCrash(Player _player, vector<Formation *> _existingFormations,bool &_gameOver)
{
	player = _player;
	existingFormations = _existingFormations;

	RectangleShape formationShape;
	float formationShape_Side;
	vector<EnemyPlane *> enemyPlanes;

	RectangleShape diminishedEnemyShape;//Base on this Rectangle it will be ascertain collision. Have to do this becouse oryginal enemys and player shapes (rectangles)
										//will create collision even if drawings of planes don't hit each other.
	RectangleShape diminishedPlayerShape = player.getPlayerShape();
	diminishedPlayerShape.setScale(0.6, 0.6);//Have to rescale rectangles. Small cheat
	
	for (int i = 0; i < existingFormations.size(); i++)
	{
		formationShape_Side = existingFormations[i]->getFormationLenght();
		formationShape.setPosition(existingFormations[i]->getFormationPosition());
		formationShape.setSize(sf::Vector2f(formationShape_Side, formationShape_Side));

		if (collisionOccurred(diminishedPlayerShape, formationShape))
		{
			enemyPlanes = existingFormations[i]->getEnemyPlanes();
			for (int j = 0; j < enemyPlanes.size(); j++)
			{
				diminishedEnemyShape = enemyPlanes[j]->getEnemyShape();
				diminishedEnemyShape.setScale(0.6, 0.6);
				
				if (missileInsideFormation(diminishedEnemyShape, diminishedPlayerShape))
				{
					_gameOver = true;
				}
			}
		}
	}
}
bool Collision::collisionOccurred(RectangleShape _object1, RectangleShape _object2) 
{
	return _object1.getGlobalBounds().intersects(_object2.getGlobalBounds());
}
void Collision::updateHit(vector<PlayerMissiles *> _playerMissilesVector, Player & _player)
{
	//now existingFormation vector is updated becouse this method is called always after updateColision()
	playerMissilesVector = _playerMissilesVector;
	vector<EnemyPlane *> enemyPlanes;
	RectangleShape formationShape;
	float formationShape_Side;
	
	for (int k = 0; k < playerMissilesVector.size(); k++)
	{
		for (int i = 0; i < existingFormations.size(); i++)
		{
			formationShape_Side = existingFormations[i]->getFormationLenght();//create rectangleShape that overlap whole formation
			formationShape.setPosition(existingFormations[i]->getFormationPosition());
			formationShape.setSize(sf::Vector2f(formationShape_Side, formationShape_Side));

			if (missileInsideFormation(playerMissilesVector[k]->getMissilesShape(), formationShape))
			{
				enemyPlanes = existingFormations[i]->getEnemyPlanes();
				for (int j = 0; j < enemyPlanes.size(); j++)
				{
					if (collisionOccurred(playerMissilesVector[k]->getMissilesShape(), enemyPlanes[j]->getEnemyShape()))
					{
						enemyPlanes[j]->collisionOccurred();//switch parameter collision on true
						playerMissilesVector[k]->collisionOccured();//switch parameter collision on true
						_player.addPointsToScore();
					}
				}
			}
		}
	}
}
bool Collision::missileInsideFormation(RectangleShape _misslieShape, RectangleShape _formationShape)
{
	return _misslieShape.getGlobalBounds().intersects(_formationShape.getGlobalBounds());
}
Collision::~Collision(){}
