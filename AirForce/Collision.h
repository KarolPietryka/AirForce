#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Formation.h"
#include <vector>

using namespace std;
using namespace sf;
class Collision
{
public:
	Collision();
	void updateCrash(Player _player, vector<Formation *>  _existingFormations, bool &_gameOver);
	void updateHit(vector<PlayerMissiles *> playerMissilesVector, Player & _player);
	bool collisionOccurred(RectangleShape _object1, RectangleShape _object2);
	bool missileInsideFormation(RectangleShape _misslieShape, RectangleShape _formationShape);
	~Collision();
private:
	Player player;
	vector<Formation *> existingFormations;
	vector<PlayerMissiles *> playerMissilesVector;
};

