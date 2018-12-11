	#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include "ILogicManager.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "UserInputType.h"
#include "DataUpdate.h"

class GameLevel : public ILogicManager {
public:
	GameLevel();

	//destructor
	//~GameLevel();

	// create all the clases thet form GameLevel
	void createLevel(LogicData);

	// evaluate and perform the user's command
	void executeUserCommand(UserInputType);

	std::vector<std::string> getLevelState();

	// check if game is over
	bool checkGameOver();

private:
	// check if the player would collide with a wall
	bool checkWallCollision(int, int);

	// check if the player would collide with an enemy
	bool checkEnemyCollision(int, int);

	// check if the player would collide with a power up
	bool checkPowerUpCollision(int, int);

	//bool checkHitCollision(int, int, int);


	int mapArray[20][20];   /// map
	int powerUpMap[20][20]; /// array with Power-Ups locations
	std::vector<std::shared_ptr<Enemy>> enemies;  /// list of enemies
	std::vector<std::shared_ptr<PowerUp>> powerUps; /// list of Power-Ups
	Player* player1; /// player
	bool isGameOver{false}; /// indicate if the game is over
	bool isGameFinished{false}; /// indicate if the level is finished
  std::vector<std::shared_ptr<DataUpdate>> output;

};

#endif // !GAMELEVEL_H
