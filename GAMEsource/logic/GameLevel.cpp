
#include <iostream>
#include <sstream>
#include <cmath>
#include <array>
#include <memory>
#include "GameLevel.h"
#include "DataToolkit.h"
#include "CharacterOrientation.h"


// constructor
GameLevel::GameLevel() {
	this->gameState = GameState::NOTLOADED;
};


// create all the objects in game level
void GameLevel::createLevel(LogicData inputString, bool keepPlayerState = false) {

	//delete(this->player1); //This one is deleted later on if necessary
	enemies.clear();
	powerUps.clear();
	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = 0; j < width; j++)
		{
			mapArray[i][j] = 1;
		}
	}
	isGameFinished = false;


	std::vector <std::string> objectVector;
	std::vector <std::string> tempConstructorData;

	// separateObjects function creates a vector of string corresponding to different objects
	objectVector = DataToolkit::getSubs(inputString.data, ';');
	
	// Handling each string object in objectVector
	for (unsigned int i{ 0 }; i < objectVector.size(); ++i) {

		std::size_t amp = objectVector[i].find("&"); //<TO DO> check if we can specify a specific type

		std::string initialChar{ objectVector[i].at(0) }; // String containing the first character of a string 
		int objectType{stoi(initialChar)}; // Conv is the integer corresponding to the first character of a string

		switch (objectType) {
			case 0: { // 0 is map
				// erase the part of the string that contains the object type and the ampersand symbol
				objectVector[i].erase(0, amp + 1);

				//loop through the map data
				unsigned int row{ 0 };
				unsigned int column{ 0 };
				for (unsigned int value{ 0 }; value < objectVector[i].size(); value++) {
					int tempValue = objectVector[i].at(value);
				
					if (tempValue == 45) { // if dash, add row
						column = 0;
						row++;

						if (row > height) throw std::length_error("The map exceded the maximum height");
					}
					else {
						mapArray[row][column] = tempValue - 48;
						column++;
						if (column > height) throw std::length_error("The map exceded the maximum width");
					}
				}
				break;
			}
			case 1: { //1 is player

				//erase the part of the string that contains the object type and the ampersand symbol
				objectVector[i].erase(0, amp + 1);

				//separate the data to construct the new object
				tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');
				int xPos = stoi(tempConstructorData[1]);
				int yPos = stoi(tempConstructorData[2]);

				if (xPos < 0 || xPos > width) throw std::invalid_argument("The player has to be inside the map");
				if (yPos < 0 || yPos > height) throw std::invalid_argument("The player has to be inside the map");

				//create a new player and save a  pointer to it
				if ((player1 != NULL) && (keepPlayerState == true)) {
					player1->setXPosition(xPos);
					player1->setYPosition(yPos);
				}
				else {
					if (player1 != NULL) player1.reset();
					player1 = std::make_unique<Player>(tempConstructorData[0], xPos,
						yPos, stoi(tempConstructorData[3]), (CharacterOrientation)stoi(tempConstructorData[4]), stoi(tempConstructorData[5])); // Added tempContructorData[4] for orientation
				}
				
				tempConstructorData = {}; //make sure the vector is empty in the next case <TO DO> make sure if this is needed
				break;
			}
			case 2: { // 2 is an enemy
				// erase the part of the string that contains the object type and the ampersand symbol
				objectVector[i].erase(0, amp + 1);

				// separate the data to construct the new object
				tempConstructorData = DataToolkit::getSubs(objectVector[i],',');

				// create a new enemy storing a shared pointer to it
				std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(tempConstructorData[0], stoi(tempConstructorData[1]),
					stoi(tempConstructorData[2]), stoi(tempConstructorData[3]), stoi(tempConstructorData[4]));

				// store the pointer in the vector enemies
				enemies.push_back(std::move(enemy));

				tempConstructorData = {}; // make sure the vector is empty in the next case
				break;
			}
			case 3: { // 3 is a Power Up 
				// erase the part of the string that contains the object type and the ampersand symbol
				objectVector[i].erase(0, amp + 1);

				// separate the data to construct the new object
				tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');

				// create a new PowerUp and save a shared vector to it 
				std::unique_ptr<PowerUp> powerUp = std::make_unique<PowerUp>(tempConstructorData[0], stoi(tempConstructorData[1]),
					stoi(tempConstructorData[2]), stoi(tempConstructorData[3]));

				// store the pointer in the vector poweUps
				powerUps.push_back(std::move(powerUp));

				tempConstructorData = {}; // make sure the vector is empty in the next case

				break;
			}
			case 4: { // 4 is a Weapon 
				// erase the part of the string that contains the object type and the ampersand symbol
				objectVector[i].erase(0, amp + 1);

				// separate the data to construct the new object
				tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');

				// create a new PowerUp and save a shared vector to it 
				std::unique_ptr<Weapon> weapon = std::make_unique<Weapon>(tempConstructorData[0], stoi(tempConstructorData[1]),
					stoi(tempConstructorData[2]), stoi(tempConstructorData[3]));

				// store the pointer in the vector poweUps
				weapons.push_back(std::move(weapon));

				tempConstructorData = {}; // make sure the vector is empty in the next case

				break;
			}
		}
	}
	this->gameState = GameState::UPANDRUNNING;
}

///  execute the input of the data
void GameLevel::executeUserCommand(UserInputType userInput) {

	output.clear(); // empty the output vector

	bool movement = true; // boolean that sais if the player is going to move
	DataUpdate::Action playerAction = DataUpdate::Action::NOTHING;

	// check the current position of the player
	int tempX = player1->getXPosition();               
	int tempY = player1->getYPosition();	
	CharacterOrientation tempOrientation = player1->getR();
	// check which position the player will go to based on the user input

	switch (userInput) {
	case UserInputType::Nothing: // No movement
		movement = false; // if no user input, no movement
		break;

	case UserInputType::Up: // Move Up
		if (tempOrientation != CharacterOrientation::Up) {
			player1->setR(CharacterOrientation::Up);
			movement = false;
		}
		else {
			tempY--;
		}
		break;
	case UserInputType::Right: // Move Right
		if (tempOrientation != CharacterOrientation::Right) {  // TO DO combine 4 checks of orientation in one
			player1->setR(CharacterOrientation::Right);
			movement = false;
		}
		else {
			tempX++;
		}
		break;
	case UserInputType::Down: // Move Down
		if (tempOrientation != CharacterOrientation::Down) {
			player1->setR(CharacterOrientation::Down);
			movement = false;
		}
		else {
			tempY++;
		}
		break;
	case UserInputType::Left: // Move Left
		if (tempOrientation != CharacterOrientation::Left) {
			player1->setR(CharacterOrientation::Left);
			movement = false;
		}
		else {
			tempX--;
		}
		break;

	case UserInputType::Drop: // Drop a weapon
		// put the weapon back in the game
		if (player1->getWeapon() != "0") {
			for (int i = 0; i < weapons.size(); i++) {
				if (weapons[i]->getID() == player1->getWeapon())
				{
					int weaponX = player1->getXPosition();
					int weaponY = player1->getYPosition();
						// find the first free spot to put it
					for (int dely : {0, -1, 1}) {
						for (int delx : {-1, 0, 1}) {
							if (!checkWallCollision(weaponX + delx, weaponY + dely) && !(delx==0 && dely==0)) {
								weaponX += delx;
								weaponY += dely;
								goto setPos;
							}
						}
					}
					setPos:
					weapons[i]->setXPosition(weaponX);
					weapons[i]->setYPosition(weaponY);
					std::shared_ptr<DataUpdate> dropWeapon(new DataUpdate(weapons[i]->getID(), weapons[i]->getXPosition(), weapons[i]->getYPosition(), weapons[i]->dataToString(), DataUpdate::ObjectType::WEAPON, DataUpdate::Action::NOTHING));
					this->output.push_back(dropWeapon);
					break;
				}
			}		
		}
		// remove the weapon from the player
		player1->dropWeapon();
		break;

	case UserInputType::Hit: { // Attack
		movement = false;	//Making sure that hitting does not end up in movement
		// Send an update to play the attack animation
		std::shared_ptr<DataUpdate> update(new DataUpdate(player1->getID(), player1->getXPosition(), player1->getYPosition(),
			player1->dataToString(), DataUpdate::ObjectType::PLAYER, DataUpdate::Action::ATTACK));
		output.push_back(update);


		switch (tempOrientation) {
		case CharacterOrientation::Up:
			tempY--;
			break;
		case CharacterOrientation::Right:
			tempX++;
			break;
		case CharacterOrientation::Down:
			tempY++;
			break;
		case CharacterOrientation::Left:
			tempX--;
			break;
		}

		for (unsigned int i{ 0 }; i < enemies.size(); i++) {

			// Process all enemies that are hit
			if (enemies[i]->getXPosition() == tempX && enemies[i]->getYPosition() == tempY) {
				if (player1->getWeapon() != "0") {
					enemies[i]->setLives(-(player1->getDmg() + 10));
				}
				else {//player1->getWeapon() returns an ID
					enemies[i]->setLives(-player1->getDmg());
					//std::cout << enemies[i]->getLives();
				}

				// check if the enemy died
				if (enemies[i]->getLives() <= 0) {
					//play the death animation
					std::shared_ptr<DataUpdate> deadEnemy(new DataUpdate(enemies[i]->getID(), enemies[i]->getXPosition(), enemies[i]->getYPosition(), enemies[i]->dataToString(), DataUpdate::ObjectType::ENEMY, DataUpdate::Action::ELIMINATE));
					this->output.push_back(deadEnemy);
					// delete the enemy
					enemies.erase(enemies.begin() + i);
				}
				else // play a get hit animation
				{
					std::shared_ptr<DataUpdate> hitEnemy(new DataUpdate(enemies[i]->getID(), enemies[i]->getXPosition(), enemies[i]->getYPosition(), enemies[i]->dataToString(), DataUpdate::ObjectType::ENEMY, DataUpdate::Action::GET_HIT));
					this->output.push_back(hitEnemy);
				}

			}

		}
	} break;


		

	
	}

		// check whether the movement is valid and if it is perform it 
		if (movement) {// if there is valid input
			if (checkWallCollision(tempX, tempY)) {}     // Check for wall collision
			else if (checkEnemyCollision(tempX, tempY)) {
				//send update to play a GET_HIT animation
				std::shared_ptr<DataUpdate> update(new DataUpdate(player1->getID(), player1->getXPosition(), player1->getYPosition(),
					player1->dataToString(), DataUpdate::ObjectType::PLAYER, DataUpdate::Action::GET_HIT));
				output.push_back(update);
			} // Check for enemy collision
			else if (checkPowerUpCollision(tempX, tempY)) {
				//; // Check for power-up collision
				player1->setXPosition(tempX);     // if no collision, move player
				player1->setYPosition(tempY);
			}
			else {//Addition of the weapon collision detection
				checkWeaponCollision(tempX, tempY);
				player1->setXPosition(tempX);     // move player...
				player1->setYPosition(tempY);
				// If player has a weapon equipped nothing happens... If no weapon is equipped then equip the one encountered and destroy it from the map

			}

		}
	

	// Update the position of the player for the output
	std::shared_ptr<DataUpdate> update(new DataUpdate(player1->getID(), player1->getXPosition(), player1->getYPosition(),
		player1->dataToString(), DataUpdate::ObjectType::PLAYER, playerAction));
	output.push_back(update);

	
	// check if the level finish has been reached
	if (mapArray[player1->getYPosition()][player1->getXPosition()] == 2) {
		this->gameState = GameState::LEVELFINISHED;
	}

	// check if game is over
	if (player1->getLives() <= 0) this->gameState = GameState::GAMEOVER;
}

// return a vector of strings with to update the output
std::vector<std::shared_ptr<DataUpdate>> GameLevel::getLevelUpdates()
{	
	return output;
}


// Check collision with a wall
bool GameLevel::checkWallCollision(int tempX, int tempY) {
	//map = array of zeros and ones (0 = move, 1 = wall, 2 = finish(move) )
	if (mapArray[tempY][tempX] == 0 || mapArray[tempY][tempX] == 2) { // if not wall, move
		return false;
	}
	else {  
		return true;
	}

}


// Check collision with enemies
bool GameLevel::checkEnemyCollision(int tempX, int tempY) {
	bool collision = false;
	// Check vector of enemy objects 
	for (std::unique_ptr<Enemy> &enemyPtr : enemies) {   
		if ((tempX == enemyPtr->getXPosition()) && (tempY == enemyPtr->getYPosition())) {
			int damage = enemyPtr->getDamage(); // get enemy damage
			player1->setLives(-damage); // implement damage minus cause of deduction of life
			collision = true; // collision happened
		}
	}
	return collision;
}


// Check collision with weapons

bool GameLevel::checkWeaponCollision(int tempX, int tempY) {
	bool collision = false;
	// Check vector of weapon objects 
	/*for (std::unique_ptr<Weapon> &weaponPtr : weapons) {
		if ((tempX == weaponPtr->getXPosition()) && (tempY == weaponPtr->getYPosition())) {
			
			player1->setWeapon(); // set new weapon
			collision = true; // collision happened
			//weapons.erase(weapons.begin() + i);
		}
	}*/
	for (int i = 0; i < weapons.size(); i++)
	{
		if ((tempX == weapons[i]->getXPosition()) && (tempY == weapons[i]->getYPosition())) {
			player1->setWeapon(weapons[i]->getID()); // set new weapon
			//Move off the screen
			weapons[i]->setXPosition(-100);
			weapons[i]->setYPosition(-100);
			collision = true;
			std::shared_ptr<DataUpdate> collectedWeapon(new DataUpdate(weapons[i]->getID(), weapons[i]->getXPosition(), weapons[i]->getYPosition(), weapons[i]->dataToString(), DataUpdate::ObjectType::WEAPON, DataUpdate::Action::GET_WEAPON));
			this->output.push_back(collectedWeapon);
			//weapons.erase(weapons.begin() + i); don't erase, because can drop it later
			break;
		}
	}
	return collision;
}

// check power-up collision
bool GameLevel::checkPowerUpCollision(int tempX, int tempY) {
	// PowerUp array (0 = no power up, 1 = power up )
	bool anyPowerUpFound = false;
	for (int i = 0; i < powerUps.size(); i++)
	{
		if ((tempX == powerUps[i]->getXPosition()) && (tempY == powerUps[i]->getYPosition())) {
			int lives = powerUps[i]->getNrOfLives();
			player1->setLives(lives);  // implement power-up effect
			anyPowerUpFound = true;
			std::shared_ptr<DataUpdate> collectedPowerUp(new DataUpdate(powerUps[i]->getID(), powerUps[i]->getXPosition(), powerUps[i]->getYPosition(), powerUps[i]->dataToString(), DataUpdate::ObjectType::POWERUP, DataUpdate::Action::ELIMINATE));
			this->output.push_back(collectedPowerUp);
			powerUps.erase(powerUps.begin() + i);
			break;
		}
	}
	return anyPowerUpFound;
}

// check the game state
GameState GameLevel::getGameState() {
	return this->gameState;
}