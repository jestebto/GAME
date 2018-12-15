#include <stdexcept>
#include "PowerUp.h"
#include <iostream>

PowerUp::PowerUp(const std::string ID, int xPos, int yPos, int lives)
	: GameObject(ID, xPos, yPos) {
	std::cout << "I am a powerup and I am being CONSTRUCTED!\n";
	setNrOfLives(lives);
}

PowerUp::~PowerUp()
{
	std::cout << "I am a powerup and I am being destructeeeeed!\n"; // TO DO for debugging purposes
}

/// set nr of lives
void PowerUp::setNrOfLives(int lives) {
	if (lives < 0) {
		throw std::invalid_argument("The number of lives of a Power-Up must be a positive integer.");
	}
	nrOfLives = lives; 
}

/// return number of lives
int PowerUp::getNrOfLives() { return nrOfLives; }