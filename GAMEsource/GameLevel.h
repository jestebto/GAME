#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include "ILogicManager.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "UserInputType.h"

class GameLevel : public ILogicManager {
public:
	GameLevel();

	//destructor
	//~GameLevel();

	//! create all the clases thet form GameLevel
	void createLevel(LogicData);

	//! evaluate and perform the user's command
	void executeUserCommand(UserInputType);

private:
	//! check if the player would collide with a wall
	bool checkWallCollision(int, int);

	//! check if the player would collide with an enemy
	bool checkEnemyCollision(int, int);

	//! check if the player would collide with a power up
	bool checkPowerUpCollision(int, int);
	
	//! check if game is over
	void checkGameOver();

	int mapArray[20][20];   
	int powerUpMap[20][20];
	std::vector<std::shared_ptr<Enemy>> enemies;  
	std::vector<std::shared_ptr<PowerUp>> powerUps;
	Player* player1;
	bool isGameOver{false};
	bool isGameFinished{false};
};

#endif // !GAMELEVEL_H
