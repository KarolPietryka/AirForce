#pragma once
#include "stdafx.h"
#include "Formation.h"
#include <vector>

using namespace std;

class Libretto
{
public:
	Libretto();
	Libretto(sf::Vector2f _windowSize);
	Formation * createFormation(unsigned _formationLevel, unsigned _planeLevel, unsigned _speedIncrementation);
	vector <Formation *> getFormationAgenda();
	~Libretto();
private:
	sf::Vector2f windowSize;
	unsigned formationLevel_FirstLvl;
	RandGenerator generator;
	vector <Formation *> formationAgenda;
};

