
#include <iostream>
#include <sstream>
#include <cmath>
#include <array>
#include "GameLevel.h"

GameLevel::GameLevel() {

};

//prototype functions
std::vector<std::string> istov(std::string);
std::vector<std::string> separateData(std::string);

//create all the objects in game level
void GameLevel::createLevel(std::string inputString) {
	std::vector <std::string> objectVec;
	std::vector <std::string> tempConstructorData;

	// istov function creates a vector of string corresponding to different objects
	objectVec = istov(inputString);
	
	//Handling each string object in objectVec
	for (unsigned int i{ 0 }; i < objectVec.size(); ++i) {

		std::size_t amp = objectVec[i].find("&");

		std::string begg{ objectVec[i].at(0) }; //String containing the first character of a string 
		int conv{std::stoi(begg)}; // Conv is the integer corresponding to the first character of a string

		switch (conv) {
		case 0: { // 0 is map

			objectVec[i].erase(0, amp + 1);

			for (unsigned int value{ 0 }; value < objectVec[i].size(); value++) {
				int tempValue = objectVec[i].at(value);
				unsigned int row{ 0 };
				unsigned int column{ 0 };
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
			objectVec[i].erase(0, amp + 1);

			tempConstructorData = separateData(objectVec[i]);
			//create a new player
			std::shared_ptr<Player> player1 (new Player(tempConstructorData[0], stoi(tempConstructorData[1]),
			stoi(tempConstructorData[2]), stoi(tempConstructorData[3])));

			tempConstructorData = {}; //make sure the vector is empty in the next case
			break;
		}
		case 2: { // 2 is an enemy
			objectVec[i].erase(0, amp + 1);
			tempConstructorData = separateData(objectVec[i]);
			//create a new enemy
			std::shared_ptr<Enemy> enemy(new Enemy(tempConstructorData[0], stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), stoi(tempConstructorData[3]), stoi(tempConstructorData[4])));
			enemies.push_back(enemy);

			tempConstructorData = {}; //make sure the vector is empty in the next case
			break;
		}
		case 3: { // 3 is a collectable
			objectVec[i].erase(0, amp + 1);
			tempConstructorData = separateData(objectVec[i]);
			//create a new PowerUp
			std::shared_ptr<PowerUp> powerUp(new PowerUp(tempConstructorData[0], stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), stoi(tempConstructorData[3])));
			powerUps.push_back(powerUp);
			tempConstructorData = {}; //make sure the vector is empty in the next case
			break;
		}
		}
	}
}

std::vector<std::string>  istov(std::string inputString) {
	std::vector <std::string> objectVec(0); //Creating a vector of size 0 which stores string values
	std::size_t del{ 0 };

	for (unsigned int i{ 0 }; inputString.size() > 0; i++) {
		del = inputString.find(";");
		objectVec.push_back(inputString.substr(0, del));
		inputString.erase(0, del + 1);
		//cout << objectVec.at(i) << endl << endl;
	}
	return objectVec;
}

std::vector<std::string> separateData(std::string inputString) {

	std::size_t del{ 0 };
	std::vector <std::string> tempVec(0);


	while (inputString.size() > 0) {
		del = inputString.find(",");
		tempVec.push_back((inputString.substr(0, del)));
		inputString.erase(0, del + 1);
	}
	return tempVec;
}


void GameLevel::executeUserCommand(int userInput) {
	bool movement = true;

	int tempX = player1->getXPosition();               //Check for function calls  //Temporary position - X
	int tempY = player1->getYPosition();											//Temporary position - Y

	switch (userInput) {
	case 0:			// No movement
		movement = false;
		break;
	case 1:			//Move Up
		tempY++;
		break;
	case 2:			//Move Right
		tempX++;
		break;
	case 3:			 //Move Down
		tempY--;
		break;
	case 4:			//Move Left
		tempX--;
		break;
	}
	//check whether the movement is valid and if it is perform it 
	if (movement) {
		if (checkWallCollision(tempX, tempY)) {}     //Check for wall collision
		else if (checkEnemyCollision(tempX, tempY)) {} //Check for enemy collision
		else if (checkPowerUpCollision(tempX, tempY)) {} //Check for power-up collision
		else {
			player1->setXPosition(tempX);     //If no problem was encountered perform the movement and update player's position
			player1->setYPosition(tempY);
		}
	}
	if (mapArray[player1->getXPosition()][player1->getYPosition()] == 2) {
		isGameFinished = true;
	} //CHECK WINNING CONDITIONS

	//check if game is over
	checkGameOver();
}


// Helper function of class Game Level which checks collisions with walls 
bool GameLevel::checkWallCollision(int tempX, int tempY) {
	//map = array of zeros and ones (0 = move, 1 = cannot move )
	if (mapArray[tempX][tempY] == 0 || mapArray[tempX][tempY] == 2) {   // If the new position of the player is unobstracted return FALSE so no collision detected
		return false;
	}
	else {  // If the new position of the player is obstracted return TRUE so  collision detected
		return true;
	}

}


// Helper function of class Game Level which checks collisions with enemies
bool GameLevel::checkEnemyCollision(int tempX, int tempY) {
	bool collision = false;
	// Check vector of enemy objects 
	for (std::shared_ptr<Enemy> enemyPtr : enemies) {   //For a pointers to enemies in a vector
		if ((tempX == enemyPtr->getXPosition()) && (tempY == enemyPtr->getYPosition())) {

			int damage = enemyPtr->getDamage(); // get enemy damage

			player1->setLives(damage); //implement damage
			collision = true;
		}
	}
	return collision;
}

// Helper function of class Game Level which checks collisions with power ups
bool GameLevel::checkPowerUpCollision(int tempX, int tempY) {
	//PowerUp array (0 = no power up, 1 = power up )
	if (powerUpMap[tempX][tempY] == 0) {
		return false;
	}
	else {
		for (std::shared_ptr<PowerUp> powerUpPtr : powerUps) {
			if ((tempX == powerUpPtr->getXPosition()) && (tempY == powerUpPtr->getYPosition())) {
				int lives = powerUpPtr->getNrOfLives();
				player1->setLives(lives);  //possible to change for different damage values
				powerUpMap[tempX][tempY] = 0; //Update the array -- check ALSO destroy the powerup
			}
		}
		return true;
	}
}

void GameLevel::checkGameOver() {
	if (!player1->isAlive()) {
		isGameOver = true;
	}
}
