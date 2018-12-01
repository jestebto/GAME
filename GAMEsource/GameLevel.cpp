
#include <iostream>
#include <sstream>
#include <cmath>
#include <array>
#include "GameLevel.h"

GameLevel::GameLevel() {

};

//create all the objects in game level
void createLevel(std::string data) {

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
	if (map[player1->getXPosition()][player1->getYPosition()] == 2) {
		isGameFinished = true;
	} //CHECK WINNING CONDITIONS

	//check if game is over
	checkGameOver();
}


// Helper function of class Game Level which checks collisions with walls 
bool GameLevel::checkWallCollision(int tempX, int tempY) {
	//map = array of zeros and ones (0 = move, 1 = cannot move )
	if (map[tempX][tempY] == 0 || map[tempX][tempY] == 2) {   // If the new position of the player is unobstracted return FALSE so no collision detected
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
	for (Enemy* enemyPtr : enemies) {   //For a pointers to enemies in a vector
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
		for (PowerUp* powerUpPtr : powerUps) {
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
