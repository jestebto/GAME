
#include <iostream>
#include <sstream>
#include <cmath>
#include <array>
#include "GameLevel.h"
#include "DataToolkit.h"

// constructor
GameLevel::GameLevel() {
	
};


/// create all the objects in game level
void GameLevel::createLevel(LogicData inputString) {
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
				}
				else {
					mapArray[row][column] = tempValue - 48;
					column++;
				}
			}
			break;
		}
		case 1: { //1 is player

			//erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);

			//separate the data to construct the new object
			tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');

			//create a new player and save a shared pointer to it
			player1 = new Player(tempConstructorData[0], stoi(tempConstructorData[1]),

			stoi(tempConstructorData[2]), stoi(tempConstructorData[3]), stoi(tempConstructorData[4]), stoi (tempConstructorData[5])); // Added tempContructorData[4] for orientation

			tempConstructorData = {}; //make sure the vector is empty in the next case <TO DO> make sure if this is needed
			break;
		}
		case 2: { // 2 is an enemy
			// erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);

			// separate the data to construct the new object
			tempConstructorData = DataToolkit::getSubs(objectVector[i],',');

			// create a new enemy storing a shared pointer to it
			std::shared_ptr<Enemy> enemy(new Enemy(tempConstructorData[0], stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), stoi(tempConstructorData[3]), stoi(tempConstructorData[4])));

			// store the pointer in the vector enemies
			enemies.push_back(enemy);

			tempConstructorData = {}; // make sure the vector is empty in the next case
			break;
		}
		case 3: { // 3 is a Power Up 
			// erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);

			// separate the data to construct the new object
			tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');

			// create a new PowerUp and save a shared vector to it 
			std::shared_ptr<PowerUp> powerUp(new PowerUp(tempConstructorData[0], stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), stoi(tempConstructorData[3])));

			// store the pointer in the vector poweUps
			powerUps.push_back(powerUp);

			tempConstructorData = {}; //! make sure the vector is empty in the next case

			break;
		}
		}
	}
}

///  execute the input of the data
void GameLevel::executeUserCommand(UserInputType userInput) {

	output.clear(); //! empty the output vector

	bool movement = true; //! boolean that sais if the player is going to move
	DataUpdate::Action playerAction = DataUpdate::Action::NOTHING;

	//! check the current position of the player
	int tempX = player1->getXPosition();               
	int tempY = player1->getYPosition();	
	int tempR = player1->getR();
	//! check which position the player will go to based on the user input

	switch (userInput) {
	case UserInputType::Nothing: // No movement
		movement = false; // if no user input, no movement
		break;

	case UserInputType::Up: //!< Move Up
		if (tempR != 2) {
			player1->setR(2);
			movement = false;
		}
		else {
			tempY--;
		}
		break;
	case UserInputType::Right: //!< Move Right
		if (tempR != 3) {  // TO DO combine 4 checks of orientation in one
			player1->setR(3);
			movement = false;
		}
		else {
			tempX++;
		}
		break;
	case UserInputType::Down: //!< Move Down
		if (tempR != 4) {
			player1->setR(4);
			movement = false;
		}
		else {
			tempY++;
		}
		break;
	case UserInputType::Left: //!< Move Left
		if (tempR != 5) {
			player1->setR(5);
			movement = false;
		}
		else {
			tempX--;
		}
		break;
	case UserInputType::Hit: // Get 'em
		
			switch (tempR) {
			case 2:
				for (std::shared_ptr<Enemy> enemyPtr : enemies) {
					if (enemyPtr->getXPosition() == tempX && enemyPtr->getYPosition() == tempY - 1) {
						enemyPtr->setLives(enemyPtr->getLives() - player1->getDmg());
						
					}
				}
				
				break;
			case 3:
				for (std::shared_ptr<Enemy> enemyPtr : enemies) {
					if (enemyPtr->getXPosition() == tempX + 1 && enemyPtr->getYPosition() == tempY) {
						enemyPtr->setLives(enemyPtr->getLives() - player1->getDmg());
						
					}
				}
				
				break;
			case 4:
				for (std::shared_ptr<Enemy> enemyPtr : enemies) {
					if (enemyPtr->getXPosition() == tempX && enemyPtr->getYPosition() == tempY + 1) {
						enemyPtr->setLives(enemyPtr->getLives() - player1->getDmg());
						
					}
				}
				
				break;
			case 5:
				for (std::shared_ptr<Enemy> enemyPtr : enemies) {
					if (enemyPtr->getXPosition() == tempX - 1 && enemyPtr->getYPosition() == tempY) {
						enemyPtr->setLives(enemyPtr->getLives() - player1->getDmg());
						
					}
				}
				
				break;
			}
			

		
		

		break;
	}

	// check whether the movement is valid and if it is perform it 
	if (movement) {// if there is valid input
		if (checkWallCollision(tempX, tempY)) {}     // Check for wall collision
		else if (checkEnemyCollision(tempX, tempY)) {} // Check for enemy collision
		else if (checkPowerUpCollision(tempX, tempY)) {} // Check for power-up collision
		else {
			player1->setXPosition(tempX);     // if no collision, move player
			player1->setYPosition(tempY);
		}
	}

	// check if the finish has been reached
	if (mapArray[player1->getXPosition()][player1->getYPosition()] == 2) {
		isGameFinished = true;
	} 
	//! Update the position of the player for the output
	std::shared_ptr<DataUpdate> update(new DataUpdate(player1->getID(), player1->dataToString(), DataUpdate::ObjectType::PLAYER, playerAction));
	output.push_back(update);

	// check if game is over
	checkGameOver();
}

/// return a vector of strings with to update the output
std::vector<std::string> GameLevel::getLevelState()
{	
	std::vector<std::string> data;

	data.push_back(player1->dataToString());

	for (std::shared_ptr<Enemy> enemyPtr : enemies) {
		data.push_back(enemyPtr->dataToString());
	}

	for (std::shared_ptr<PowerUp> powerUpPtr : powerUps) {
		data.push_back(powerUpPtr->dataToString());
	}
	return data;
}


/// Check collision with a wall
bool GameLevel::checkWallCollision(int tempX, int tempY) {
	//map = array of zeros and ones (0 = move, 1 = wall, 2 = finish(move) )
	if (mapArray[tempY][tempX] == 0 || mapArray[tempY][tempX] == 2) { // if not wall, move
		return false;
	}
	else {  
		return true;
	}

}


/// Check collision with enemies
bool GameLevel::checkEnemyCollision(int tempX, int tempY) {
	bool collision = false;
	// Check vector of enemy objects 
	for (std::shared_ptr<Enemy> enemyPtr : enemies) {   
		if ((tempX == enemyPtr->getXPosition()) && (tempY == enemyPtr->getYPosition())) {
			int damage = enemyPtr->getDamage(); // get enemy damage
			player1->setLives(-damage); // implement damage minus cause of deduction of life
			collision = true; // collision happened
		}
	}
	return collision;
}

/// check power-up collision
bool GameLevel::checkPowerUpCollision(int tempX, int tempY) {
	// PowerUp array (0 = no power up, 1 = power up )
	if (powerUpMap[tempX][tempY] == 0) {
		return false;
	}
	else {
		for (std::shared_ptr<PowerUp> powerUpPtr : powerUps) {
			if ((tempX == powerUpPtr->getXPosition()) && (tempY == powerUpPtr->getYPosition())) {
				int lives = powerUpPtr->getNrOfLives();
				player1->setLives(lives);  // implement power-up effect
				powerUpMap[tempX][tempY] = 0; // Update the array
			}
		}
		return true;
	}
}

/// check if the game is over
bool GameLevel::checkGameOver() {
	if (!player1->isAlive()) {
		isGameOver = true;
		return true;
	}
	else {
		return false;
	}
}