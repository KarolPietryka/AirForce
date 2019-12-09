// AirForce.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Engine.h"

using namespace std;
using namespace sf;
int main()
{
	sf::RenderWindow window(sf::VideoMode(1024, 762), "AirForces", sf::Style::Close | sf::Style::Resize);
	window.setVerticalSyncEnabled(true);

	Engine engine((float)window.getSize().x, (float)window.getSize().y);
	float deltaTime = 0.0f;
	sf::Clock clockAnimationTime;
	sf::Clock clockplayerFireSpeed;
	sf::Clock clockFormationTime;
	sf::Clock clockBackGroundTime;

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case (Event::Closed):
					window.close();
					break;
			}
		}
		
		if (!engine.isGameOver())
		{
			engine.updatePlayer(clockAnimationTime);
			engine.playerFire(clockplayerFireSpeed);
			engine.updateMissiles();
			engine.createFormation(clockFormationTime);
			engine.updateCollision();
			engine.updateFormation();
			engine.updateVisualEffect();
			engine.updateBackGround(clockBackGroundTime);
			engine.isGameCompleted();
			
			window.clear(sf::Color::Black);
			engine.drawBackGround(window);
			engine.drawExplosion(window);
			engine.drawMissiles(window);
			engine.drawPlayer(window);
			engine.drawEnemyFormation(window);
			engine.drawBestScore(window);
			window.display();
		}
		else//gameover screan with no updates
		{
			window.clear(sf::Color::Black);
			engine.drawBackGround(window);
			engine.drawExplosion(window);
			engine.drawMissiles(window);
			engine.drawPlayer(window);
			engine.drawEnemyFormation(window);
			engine.drawBestScore(window);
			engine.drawGameOver(window);
			engine.drawScore(window);
			engine.updateBestScore();
			window.display();			
		}
	}
}

