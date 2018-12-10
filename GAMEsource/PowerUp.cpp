#include <stdexcept>
#include "PowerUp.h"

PowerUp::PowerUp(const std::string ID, int xPos, int yPos, int lives)
	: GameObject(ID, xPos, yPos) {
	setNrOfLives(lives);
}

/// set nr of lives
void PowerUp::setNrOfLives(int lives) {
	if (lives < 0) {
		throw std::invalid_argument("The number of lives must be > 0");
	}
	nrOfLives = lives; 
}

/// return number of lives
int PowerUp::getNrOfLives() { return nrOfLives; }