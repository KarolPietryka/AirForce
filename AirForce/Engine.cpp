#include "stdafx.h"
#include "Engine.h"


Engine::Engine(float _windowSizeX, float _windowSizeY) : windowSizeX(_windowSizeX), windowSizeY(_windowSizeY)
{
	lastGeneratedFormation = -1;
	formationGeneratorSpeed = 2.3f;
	delatedFormations = 0; //number of destoryed formations or formations that was deleted becouse of outOfWindow 
	bestScore = readBestScore();
	player = Player(windowSizeX, windowSizeY);
	libretto = Libretto(sf::Vector2f(windowSizeX,windowSizeY));

	formationAgenda = libretto.getFormationAgenda();

	//backGround
	float switchTimeOfBackGroundAnimation = 1.0f;
	backGroundShape.setPosition(0, 0);//sets start position
	backGroundShape.setSize(sf::Vector2f(windowSizeX, windowSizeY));
	
	sf::Image image;
	image.loadFromFile("img/background2_Final2_v2.0.png");

	backGroundTexture->loadFromImage(image);
	backGroundShape.setTexture(backGroundTexture);

	backGroundAnimations = new BackGroundAnimations(backGroundTexture, switchTimeOfBackGroundAnimation);
	//backGround

	//gameOver
	gameOverShape.setSize(sf::Vector2f(windowSizeX / 2, windowSizeY / 2));
	gameOverShape.setOrigin(gameOverShape.getSize().x / 2, gameOverShape.getSize().y / 2);
	gameOverShape.setPosition(sf::Vector2f(windowSizeX / 2 , windowSizeY / 2));

	image.loadFromFile("img/game_over2.png");
	image.createMaskFromColor(sf::Color::White);

	gameOverTexture->loadFromImage(image);
	gameOverShape.setTexture(gameOverTexture);
	//gameOver
}
void Engine::setTextureRecforPlayer(const IntRect & rectangle)
{
	player.getPlayerShape().setTextureRect(rectangle);//player.playerShape.setTextureRect(rectangle);
}
Player & Engine::getPlayer()
{
	return player;
}
void Engine::playerFire(sf::Clock & _playerFireSpeedClock)//creates new missiles and push it to vector
{
	PlayerMissiles  * playerMissiles;
	playerMissiles = player.fire(_playerFireSpeedClock);//fire processing. Create missile. If conditions are no fulfil
	if (!(playerMissiles->getMissilesShape().getPosition().x == -1))//conditions no sate
	{
		playerMissilesVector.push_back(playerMissiles);
	}
	else
	{
		delete playerMissiles;
		playerMissiles = NULL;
	}
}
void Engine::createFormation(sf::Clock &_clockFormationTime)
{
	Formation *nextFormation;
	if (_clockFormationTime.getElapsedTime().asSeconds() >= formationGeneratorSpeed &&
		lastGeneratedFormation != formationAgenda.size() - 1)//limits number of genereted formations
	{
		_clockFormationTime.restart();
		nextFormation = formationAgenda[++lastGeneratedFormation];
		existingFormations.push_back(nextFormation);
	}
}
vector<PlayerMissiles *> Engine::getPlayerMissilesVector()
{
	return playerMissilesVector;
}
bool Engine::isGameOver()
{
	return gameOver;
}
bool Engine::isGameCompleted()
{
	if (formationAgenda.size() == delatedFormations)
	{
		gameOver = true;
	}
	return gameOver;
}
int Engine::readBestScore()
{
	ifstream randNumFile_Read("BestScore.txt");
	int bestScore;
	int playerScore = player.getScore();
	if (randNumFile_Read.is_open())
	{
		string line;
		while (getline(randNumFile_Read, line))
		{
			bestScore = stoi(line);
		}
		randNumFile_Read.close();
	}
	return bestScore;
}

void Engine::updatePlayer(sf::Clock &_clock)
{
	player.movePlayer(_clock);
}
void Engine::updateMissiles() 
{
	sf::Vector2f missilePosition;
	for (int i = 0; i < playerMissilesVector.size(); i++)//do not del warning
	{
		int k = i;
		missilePosition = playerMissilesVector[i]->getMissilesShape().getPosition();
		updateMissiles_OutOfWindow(missilePosition, i);
		if (playerMissilesVector.size() != 0)//if formation is empty then delete the formation
		{
			updateMissiles_Collision(k);
		}
	}
}
void Engine::updateMissiles_OutOfWindow(sf::Vector2f _missilePosition, int &i)
{
	if (_missilePosition.x > 0 && _missilePosition.x < windowSizeX &&//check if missile are in window
		_missilePosition.y > 0 && _missilePosition.y < windowSizeY)
	{
		playerMissilesVector[i]->moveMissiles();
	}
	else
	{
		delete playerMissilesVector[i];
		playerMissilesVector.erase(playerMissilesVector.begin() + i);
		i--;
	}
}
void Engine::updateMissiles_Collision(int &i)
{
	if (playerMissilesVector[i]->getCollisionStatus())
	{
		delete playerMissilesVector[i];
		playerMissilesVector.erase(playerMissilesVector.begin() + i);
		i--;
	}
}
void Engine::updateBackGround(sf::Clock _clock)
{
	backGroundAnimations->updateBackGroundAnimation(_clock);
	IntRect rec = backGroundAnimations->uvRect;
	backGroundShape.setTextureRect(rec);
}
void Engine::updateFormation()
{
	vector<EnemyPlane *> enemyPlanesVector;
	sf::Vector2f enemyPosition;

	Explosion * explosion;
	float enemySize;

	for (int i = 0; i < existingFormations.size(); i++)//do not del this warning
	{
		enemyPlanesVector = existingFormations[i]->getEnemyPlanes();
		existingFormations[i]->moveFormation(enemyPlanesVector);
		if (enemyPlanesVector.size() == 0)//if formation is empty then delete the formation //TODO:
		{
			delete existingFormations[i];
			existingFormations.erase(existingFormations.begin() + i);
			i--;
			delatedFormations++;
		}
		for (int j = 0; j < enemyPlanesVector.size(); j++) // do not del warning
		{
			int k = j;
			enemyPosition = enemyPlanesVector[j]->getEnemyShape().getPosition();
			updadeFormation_Move(enemyPosition, enemyPlanesVector, i, j);
			if (enemyPlanesVector.size() == 0)//if formation is empty then delete the formation //TODO:
			{
				delete existingFormations[i];
				existingFormations.erase(existingFormations.begin() + i);
				i--;
				delatedFormations++;
			}
			else
			{
				if (k >= existingFormations[i]->getEnemyPlanes().size())
				{
					k--;
				}
				updateFormation_Collision(enemyPosition, enemyPlanesVector, i, k);
			}
		}
	}
}
void Engine::updadeFormation_Move(sf::Vector2f _enemyPosition, vector<EnemyPlane *> &_enemyPlanesVector, int &i, int &j)
{
	if (_enemyPosition.x > 0 && _enemyPosition.x < windowSizeX &&//if enemy plane is out of window
		_enemyPosition.y <= windowSizeY)
	{
		_enemyPlanesVector[j]->moveEnemy();
	}
	else
	{
		updateFormation_OutOfWindow(_enemyPlanesVector, i, j);
	}
}
void Engine::updateFormation_OutOfWindow(vector<EnemyPlane *> &_enemyPlanesVector, int &i, int &j)//Delete enemyPlanes if out of Window
{
	delete _enemyPlanesVector[j];
	_enemyPlanesVector.erase(_enemyPlanesVector.begin() + j);
	existingFormations[i]->getEnemyPlanes() = _enemyPlanesVector;//redefine existingFormation
	j--;	
}
void Engine::updateFormation_Collision(sf::Vector2f _enemyPosition, vector<EnemyPlane *> &_enemyPlanesVector,  int &i, int &j)//Delete enemyPlanes if enemyPlane was hit, add expolosion to explosionVector
{
	Explosion * explosion;

	if (_enemyPlanesVector[j]->getCollisionStatus())//there is enemyPlane who was hit
	{
		_enemyPosition = _enemyPlanesVector[j]->getEnemyShape().getPosition();
		float enemySize = _enemyPlanesVector[j]->getEnemyShape().getSize().x;

		explosion = new Explosion(_enemyPosition, enemySize);//Explosion must occurred in the last enemyPlane place
		explosionVector.push_back(explosion);

		delete _enemyPlanesVector[j];//delete enemyPlane from formation;
		_enemyPlanesVector.erase(_enemyPlanesVector.begin() + j);
		existingFormations[i]->getEnemyPlanes() = _enemyPlanesVector;//redefine existingFormation
		j--;
	}
}
void Engine::updateCollision()
{
	collisionEngine.updateCrash(player, existingFormations, gameOver);//asign (update every time when updateCollision is called) existingFormation to existingFormation field
	collisionEngine.updateHit(playerMissilesVector, player);
}
/*void Engine::updateBattleField()//TO DEL?
{
	vector<EnemyPlane *> enemyPlanesVector;
	Explosion * explosion;

	sf::Vector2f enemyPosition;
	float enemySize;

	for (int i = 1; existingFormations.size(); i++)//search for hit enemyPlane
	{
		enemyPlanesVector = existingFormations[i]->getEnemyPlanes();
		for (int j = 0; j < enemyPlanesVector.size(); j++)
		{
			if (enemyPlanesVector[j]->getCollisionStatus())//there is enemyPlane who was hit
			{
				enemyPosition = enemyPlanesVector[j]->getEnemyShape().getPosition();
				enemySize = enemyPlanesVector[j]->getEnemyShape().getSize().x;

				explosion = new Explosion(enemyPosition, enemySize);
				explosionVector.push_back(explosion);

				delete enemyPlanesVector[j];//delete enemyPlane from formation;
				enemyPlanesVector.erase(enemyPlanesVector.begin() + j);
				existingFormations[i]->getEnemyPlanes() = enemyPlanesVector;//redefine existingFormation
				j--;
			}
		}
		if (existingFormations[i]->getEnemyPlanes().size() == 0)
		{
			delete existingFormations[i];
			existingFormations.erase(existingFormations.begin() + i);
			i--;
		}
	}
	for (int k = 0; k < playerMissilesVector.size(); k++)
	{

			
		
	}
}*/
void Engine::updateVisualEffect()
{
	for (int i = 0; i < explosionVector.size(); i++)
	{
		if (explosionVector[i]->getAnimations()->getAnimationFinishedStatus())
		{
			delete explosionVector[i];//delete enemyPlane from formation;
			explosionVector.erase(explosionVector.begin() + i);
			i--;
		}
		else
		{
			explosionVector[i]->upDateAnimation();
		}
	}
}
void Engine::updateBestScore()
{
	int playerScore = player.getScore();
	if (bestScore < playerScore)
	{
		ofstream randNumFile_Write("BestScore.txt");
		if (randNumFile_Write.is_open())
		{
			randNumFile_Write << playerScore;
			randNumFile_Write.close();
		}
	}
}

void Engine::drawBackGround(sf::RenderWindow &_window)
{
	_window.draw(backGroundShape);
}
void Engine::drawMissiles(sf::RenderWindow &_window)
{
	PlayerMissiles *playerMissiles;
	for (int i = 0, iLen = playerMissilesVector.size(); i < iLen; i++)
	{
		playerMissiles = playerMissilesVector[i];
		_window.draw(*playerMissiles);
	}
}
void Engine::drawPlayer(sf::RenderWindow &_window)
{
	_window.draw(player);
}
void Engine::drawEnemyFormation(sf::RenderWindow & _window)
{
	vector<EnemyPlane *> enemyPlanes;
	for (int i = 0, len = existingFormations.size(); i < len; i++)
	{
		enemyPlanes = existingFormations[i]->getEnemyPlanes();
		for (int j = 0, len = enemyPlanes.size(); j < len; j++)
		{
			_window.draw(*enemyPlanes[j]);
		}
	}
}
void Engine::drawExplosion(sf::RenderWindow & _window)
{
	for (int i = 0, len = explosionVector.size(); i < len; i++)
	{
		_window.draw(*explosionVector[i]);
	}
}
void Engine::drawGameOver(sf::RenderWindow & _window)
{
	_window.draw(gameOverShape);
}
void Engine::drawScore(sf::RenderWindow & _window)
{
	sf::Font font;
	sf::Text text;

	if (!font.loadFromFile("fonts/FontFile.ttf"))
	{
		cout << "Error load font file" << endl;
	}

	if (bestScore < player.getScore())
	{
		text.setString("New Best Score:  " + to_string(player.getScore()));
	}
	else
	{
		text.setString("Score:  " + to_string(player.getScore()));
	}
	text.setFont(font);
	text.setPosition(sf::Vector2f((windowSizeX / 2) - (windowSizeX / 6), (windowSizeY / 2) + (windowSizeX / 6)));
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(140);

	_window.draw(text);	
}
void Engine::drawBestScore(sf::RenderWindow & _window)
{
	sf::Font font;
	sf::Text text;

	if (!font.loadFromFile("fonts/FontFile.ttf"))
	{
		cout << "Error load font file" << endl;
	}

	text.setFont(font);
	text.setString("Best Score:  " + to_string(bestScore));
	text.setPosition(sf::Vector2f(0, 0));
	text.setFillColor(sf::Color::Black);
	text.setCharacterSize(80);

	_window.draw(text);
}

Engine::~Engine()
{
}
