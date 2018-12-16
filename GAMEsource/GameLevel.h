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
	void createLevel(LogicData, bool);

	// evaluate and perform the user's command
	void executeUserCommand(UserInputType);

	std::vector<std::shared_ptr<DataUpdate>> getLevelUpdates();

	// check if game is over
	GameState getGameState();

private:
	// check if the player would collide with a wall
	bool checkWallCollision(int, int);

	// check if the player would collide with an enemy
	bool checkEnemyCollision(int, int);

	// check if the player would collide with a power up
	bool checkPowerUpCollision(int, int);

	//bool checkHitCollision(int, int, int);

	GameState gameState;
	static const int height{20};
	static const int width{20};
	int mapArray[height][width];   /// map
	std::vector<std::unique_ptr<Enemy>> enemies;  /// list of enemies
	std::vector<std::unique_ptr<PowerUp>> powerUps; /// list of Power-Ups
	std::unique_ptr<Player> player1; /// player
	bool isGameOver{false}; /// indicate if the game is over
	bool isGameFinished{false}; /// indicate if the level is finished
    std::vector<std::shared_ptr<DataUpdate>> output;

};

#endif // !GAMELEVEL_H
