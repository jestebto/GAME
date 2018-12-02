
#include <iostream>
#include <sstream>
#include <cmath>
#include <array>
#include "GameLevel.h"

// constructor
GameLevel::GameLevel() {
	
};

//prototype functions
std::vector<std::string> separateObjects(std::string);
std::vector<std::string> separateData(std::string);

//! create all the objects in game level
void GameLevel::createLevel(LogicData inputString) {
	std::vector <std::string> objectVector;
	std::vector <std::string> tempConstructorData;

	//! separateObjects function creates a vector of string corresponding to different objects
	objectVector = separateObjects(inputString.data);
	
	//! Handling each string object in objectVector
	for (unsigned int i{ 0 }; i < objectVector.size(); ++i) {

		std::size_t amp = objectVector[i].find("&"); //<TO DO> check if we can specify a specific type

		std::string initialChar{ objectVector[i].at(0) }; //!< String containing the first character of a string 
		int objectType{stoi(initialChar)}; //!< Conv is the integer corresponding to the first character of a string

		switch (objectType) {
		case 0: { //!< 0 is map
			//! erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);

			//!loop through the map data
			unsigned int row{ 0 };
			unsigned int column{ 0 };
			for (unsigned int value{ 0 }; value < objectVector[i].size(); value++) {
				int tempValue = objectVector[i].at(value);
				
				if (tempValue == 45) { //!< if dash, add row
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
			tempConstructorData = separateData(objectVector[i]);
			//create a new player and save a shared pointer to it
			player1 = new Player(tempConstructorData[0], stoi(tempConstructorData[1]),
			stoi(tempConstructorData[2]), stoi(tempConstructorData[3]));
			tempConstructorData = {}; //make sure the vector is empty in the next case <TO DO> make sure if this is needed
			break;
		}
		case 2: { //!< 2 is an enemy
			//! erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);
			//! separate the data to construct the new object
			tempConstructorData = separateData(objectVector[i]);
			//! create a new enemy storing a shared pointer to it
			std::shared_ptr<Enemy> enemy(new Enemy(tempConstructorData[0], stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), stoi(tempConstructorData[3]), stoi(tempConstructorData[4])));
			//! store the pointer in the vector enemies
			enemies.push_back(enemy);
			tempConstructorData = {}; //!< make sure the vector is empty in the next case
			break;
		}
		case 3: { //!< 3 is a Power Up 
			//! erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);
			//! separate the data to construct the new object
			tempConstructorData = separateData(objectVector[i]);
			//! create a new PowerUp and save a shared vector to it 
			std::shared_ptr<PowerUp> powerUp(new PowerUp(tempConstructorData[0], stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), stoi(tempConstructorData[3])));
			//! store the pointer in the vector poweUps
			powerUps.push_back(powerUp);
			tempConstructorData = {}; //!< make sure the vector is empty in the next case
			break;
		}
		}
	}
}

//! separate the data in the input string into different sub-strings that represent different objects
std::vector<std::string>  separateObjects(std::string inputString) {
	std::vector <std::string> objectVector; //!< Creating a vector which stores string values
	std::size_t del;

	for (unsigned int i{ 0 }; inputString.size() > 0; i++) {
		//! find the symbol that separates objects (semicolon)
		del = inputString.find(";");
		//! store the data from the beggining of the string to the semicolon (not included)
		objectVector.push_back(inputString.substr(0, del));
		//! delete the stored data and the semicolon
		inputString.erase(0, del + 1);
	}
	return objectVector;
}

std::vector<std::string> separateData(std::string inputString) {
	std::vector <std::string> tempVector;
	std::size_t del;

	while (inputString.size() > 0) {
		//! find the symbol that separates the object's data (coma)
		del = inputString.find(",");
		//! store the data from the beggining of the string to the coma (not included)
		tempVector.push_back((inputString.substr(0, del)));
		//! delete the data that was stored and the coma
		inputString.erase(0, del + 1);
	}
	return tempVector;
}

//
void GameLevel::executeUserCommand(UserInputType userInput) {
	bool movement = true; //!< boolean that sais if the player is going to move
	//! check the current position of the player
	int tempX = player1->getXPosition();               
	int tempY = player1->getYPosition();											
	//! check which position the player will go to based on the user input
	switch (userInput) {
	case UserInputType::Nothing: //!< No movement
		movement = false; //!< if no user input, no movement
		break;
	case UserInputType::Up: //!< Move Up
		tempY--;
		break;
	case UserInputType::Right: //!< Move Right
		tempX++;
		break;
	case UserInputType::Down: //!< Move Down
		tempY++;
		break;
	case UserInputType::Left: //!< Move Left
		tempX--;
		break;
	}
	//! check whether the movement is valid and if it is perform it 
	if (movement) {//!< if there is valid input
		if (checkWallCollision(tempX, tempY)) {}     //!< Check for wall collision
		else if (checkEnemyCollision(tempX, tempY)) {} //!< Check for enemy collision
		else if (checkPowerUpCollision(tempX, tempY)) {} //!< Check for power-up collision
		else {
			player1->setXPosition(tempX);     //!< if no collision, move player
			player1->setYPosition(tempY);
		}
	}
	//! check if the finish has been reached
	if (mapArray[player1->getXPosition()][player1->getYPosition()] == 2) {
		isGameFinished = true;
	} 

	//! check if game is over
	checkGameOver();
}


//! Check collision with a wall
bool GameLevel::checkWallCollision(int tempX, int tempY) {
	//map = array of zeros and ones (0 = move, 1 = wall, 2 = finish(move) )
	if (mapArray[tempX][tempY] == 0 || mapArray[tempX][tempY] == 2) { //!< if not wall, move
		return false;
	}
	else {  
		return true;
	}

}


//! Check collision with enemies
bool GameLevel::checkEnemyCollision(int tempX, int tempY) {
	bool collision = false;
	//! Check vector of enemy objects 
	for (std::shared_ptr<Enemy> enemyPtr : enemies) {   
		if ((tempX == enemyPtr->getXPosition()) && (tempY == enemyPtr->getYPosition())) {
			int damage = enemyPtr->getDamage(); //!< get enemy damage
			player1->setLives(damage); //!< implement damage
			collision = true; //!< collision happened
		}
	}
	return collision;
}

//! check power-up collision
bool GameLevel::checkPowerUpCollision(int tempX, int tempY) {
	//! PowerUp array (0 = no power up, 1 = power up )
	if (powerUpMap[tempX][tempY] == 0) {
		return false;
	}
	else {
		for (std::shared_ptr<PowerUp> powerUpPtr : powerUps) {
			if ((tempX == powerUpPtr->getXPosition()) && (tempY == powerUpPtr->getYPosition())) {
				int lives = powerUpPtr->getNrOfLives();
				player1->setLives(lives);  //!< implement power-up effect
				powerUpMap[tempX][tempY] = 0; //!< Update the array
			}
		}
		return true;
	}
}

//! check game over
void GameLevel::checkGameOver() {
	if (!player1->isAlive()) {
		isGameOver = true;
	}
}