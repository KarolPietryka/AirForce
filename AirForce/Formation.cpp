#include "stdafx.h"
#include "Formation.h"
#include <windows.h>

Formation::Formation(){}
Formation::Formation(unsigned _formationLevel, unsigned _planeLevel, sf::Vector2f _windowSize, unsigned _speedIncrementation):formationLevel(_formationLevel),
																														planeLevel(_planeLevel),
																														windowSize(_windowSize),
																														speedIncrementation(_speedIncrementation)
{
	formationSize = 16;
	gapBetweenPlanes = 20;
	formationColumnAndRowSize = sqrt(formationSize);

	switch (formationLevel)
	{
	case 0:
	{
		bool formationLocal[][4] = {
										{ 0, 0, 0, 0 },
										{ 0, 0, 0, 0 },
										{ 1, 0, 0, 1 },
										{ 0, 1, 1, 0 }
		};
		bool * p = &formationLocal[0][0];
		setFormationOneZeroSet(p);
		currentNumOfPlanes = 4;//number of '1' in formation table
		break;
	}
	case 1:
	{
		bool formationLocal[][4] = {
			{ 0, 0, 0, 0 },
			{ 0, 1, 1, 0 },
			{ 1, 0, 0, 1 },
			{ 0, 1, 1, 0 }
		};
		bool * p = &formationLocal[0][0];
		setFormationOneZeroSet(p);
		currentNumOfPlanes = 6;//number of '1' in formation table
		break;
	}
	case 2:
	{
		bool formationLocal[][4] = {
			{ 1, 0, 0, 1 },
			{ 0, 1, 1, 0 },
			{ 1, 0, 0, 1 },
			{ 1, 1, 1, 1 }
		};
		bool * p = &formationLocal[0][0];
		setFormationOneZeroSet(p);
		currentNumOfPlanes = 10;//number of '1' in formation table
		break;
	}
	case 3:
	{
		bool formationLocal[][4] = {
			{ 1, 0, 0, 1 },
			{ 1, 0, 0, 1 },
			{ 1, 0, 0, 1 },
			{ 1, 0, 0, 1 }
		};
		bool * p = &formationLocal[0][0];
		setFormationOneZeroSet(p);
		currentNumOfPlanes = 8;//number of '1' in formation table
		break;
	}
	case 4:
	{
		bool formationLocal[][4] = {
			{ 1, 0, 0, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 1, 1, 1 },
			{ 1, 0, 0, 1 }
		};
		const bool * p = &formationLocal[0][0];
		setFormationOneZeroSet(p);
		currentNumOfPlanes = 10;//number of '1' in formation table
		break;
	}
	case 6:
	{
		bool formationLocal[][4] = {
			{ 1, 0, 0, 0 },
			{ 0, 1, 0, 0 },
			{ 0, 0, 1, 0 },
			{ 0, 0, 0, 1 }
		};
		bool * p = &formationLocal[0][0];
		setFormationOneZeroSet(p);
		currentNumOfPlanes = 4;//number of '1' in formation table
		break;
	}
	default:
		try
		{
			throw std::invalid_argument("invalid value in formationLevel in Formation constructor");
		}
		catch (std::invalid_argument &e)
		{
			cout << "invalid value in formationLevel in Formation constructor";
		}
	}

	setEnemyPlanesVector();

	formationLenght = sqrt(formationSize) * enemyPlanes[0]->getEnemyShape().getSize().x + (sqrt(formationSize) - 1)*gapBetweenPlanes; //lenght of formation side
	formationPosition = sf::Vector2f((formationStartLocationX - (enemyPlanes[0]->getEnemyShape().getSize().x / 2)),enemyPlanes[0]->getEnemyShape().getPosition().y - formationLenght);//left up corner of formation
}
void Formation::setFormationOneZeroSet(const bool * _p_formationLocal)
{
	for (int i = 0, len =formationSize ; i < len; i++)
	{
		formationOneZeroSet.push_back(*(_p_formationLocal++));
	}
}
void Formation::setEnemyPlanesVector()
{
	sf::Vector2f enemySizeTmp;
	EnemyPlane enemyPlaneTmp(planeLevel, 0, 0, 0);//create temporary example of enemy plane to get size. Size is need to specify position first plane in formation
	enemySizeTmp = enemyPlaneTmp.getEnemyShape().getSize();
	
	formationStartLocationX = setFirstPlanePosition();//left-bottom corner of formation
	nextPlanePositionX = formationStartLocationX;
	nextPlanePositionY = -((enemySizeTmp.y) / 2);// to start drawing enemy outside of renderwindow
	
	for (int i = (int)formationColumnAndRowSize - 1; i >= 0; i--)// way to read in row order starting from row with the highest X value if [X][Y]
	{
		for (int j = 0; j < formationColumnAndRowSize; j++)
		{
			if (formationOneZeroSet[(i * (int)formationColumnAndRowSize) + j] == 1)
			{
				EnemyPlane *enemyPlane = new EnemyPlane(planeLevel, nextPlanePositionX, nextPlanePositionY, speedIncrementation);
				enemyPlanes.push_back(enemyPlane);
			}
			nextPlanePositionX += enemySizeTmp.x + gapBetweenPlanes;
		}
		nextPlanePositionX = formationStartLocationX;
		nextPlanePositionY -= enemySizeTmp.y + gapBetweenPlanes;
	}
}
void Formation::setPositionOfEnemyPlane(EnemyPlane *_p_enemyPlane)
{
	_p_enemyPlane->getEnemyShape().setPosition({ nextPlanePositionX, nextPlanePositionY });
}
float Formation::setFirstPlanePosition()//set position based on rand generator
{
	unsigned randNum = generator.rand();

	sf::Vector2f enemyPlaneShape = EnemyPlane(planeLevel, 0, 0, 0).getEnemyShape().getSize();
	int maxPositionX = (int)windowSize.x - (int)((sqrt(formationOneZeroSet.size()) * (enemyPlaneShape.x)) + ((sqrt(formationOneZeroSet.size()) - 1) * gapBetweenPlanes));
	float formationStartLocationX = (randNum % maxPositionX) + (enemyPlaneShape.x)/2;
	return formationStartLocationX;
}
vector<EnemyPlane *> &Formation::getEnemyPlanes()
{ 
	return enemyPlanes;
}
float Formation::getFormationLenght()
{
	return formationLenght;
}
void Formation::moveFormation(vector<EnemyPlane *> enemyPlanesVector)
{
	if (enemyPlanesVector.size() != 0)
	{
		formationPosition.y += enemyPlanesVector[0]->getSpeed();
	}
}
sf::Vector2f Formation::getFormationPosition()
{
	return formationPosition;
}
Formation::~Formation()
{
}
