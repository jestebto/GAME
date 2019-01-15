#ifndef GAMELEVEL_H
#define GAMELEVEL_H

#include <vector>
#include <memory>
#include "ILogicManager.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "Weapon.h"
#include "UserInputType.h"
#include "DataUpdate.h"
/// Implements the logic part of the game through the ILogicManager interface
/**
* Owns different GameOject and level data. 
* The most important class of the logic component
*/
class GameLevel : public ILogicManager {
public:
	/// constructor
	GameLevel();

	//destructor
	//~GameLevel();

	/// create all the clases thet form GameLevel
	void createLevel(LogicData, bool);

	/// evaluate and perform the user's command
	void executeUserCommand(UserInputType);

	std::vector<std::shared_ptr<DataUpdate>> getLevelUpdates();

	/// check if game is over
	GameState getGameState();

private:
	/// check if the player would collide with a wall
	bool checkWallCollision(int, int);

	/// check if the player would collide with an enemy
	bool checkEnemyCollision(int, int);

	/// check if the player would collide with a power up
	bool checkPowerUpCollision(int, int);

	/// check if the player would collide with a weapon
	bool checkWeaponCollision(int, int);


	GameState gameState;
	static const int height{20}; /// maximum hight of the map
	static const int width{20}; /// maximum width of the map
	int mapArray[height][width];   /// map
	std::vector<std::unique_ptr<Enemy>> enemies;  /// list of enemies
	std::vector<std::unique_ptr<PowerUp>> powerUps; /// list of Power-Ups
	std::vector<std::unique_ptr<Weapon>> weapons; /// list of Weapons
	std::unique_ptr<Player> player1; /// player
	bool isGameOver{false}; /// indicate if the game is over
	bool isGameFinished{false}; /// indicate if the level is finished
    std::vector<std::shared_ptr<DataUpdate>> output; /// deta to update the output

};

#endif /* GAMELEVEL_H */

