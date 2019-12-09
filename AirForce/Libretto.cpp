#include "stdafx.h"
#include "Libretto.h"
#include <windows.h>


Libretto::Libretto() {}
Libretto::Libretto(sf::Vector2f _windowSize): windowSize(_windowSize)
{
	formationLevel_FirstLvl = 5;

	for (int j = 0; j < 2; j++)
	{
		for (int i = 0, len = 4; i < len; i++)
		{
			Formation *newFormation = createFormation(formationLevel_FirstLvl, 0, j);
			formationAgenda.push_back(newFormation);
		}
		for (int i = 0, len = 5; i < len; i++)
		{
			Formation *newFormation = createFormation(formationLevel_FirstLvl, 1, j);
			formationAgenda.push_back(newFormation);
		}
		for (int i = 0, len = 6; i < len; i++)
		{
			Formation *newFormation = createFormation(formationLevel_FirstLvl, 2, j);
			formationAgenda.push_back(newFormation);
		}
	}
}
Formation * Libretto::createFormation(unsigned _formationLevel, unsigned _planeLevel, unsigned _speedIncrementation)
{
	unsigned randNum = generator.rand();

	unsigned formationLevel = randNum % _formationLevel;
	return new Formation(formationLevel, _planeLevel, windowSize, _speedIncrementation);
}
vector <Formation *> Libretto::getFormationAgenda()
{
	return formationAgenda;
}
Libretto::~Libretto()
{
}

