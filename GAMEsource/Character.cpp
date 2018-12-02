#include "Character.h"

// constructor
Character::Character(const std::string ID, int xPos, int yPos,
	int nrLives)
	: GameObject(ID, xPos, yPos) {
	lives = nrLives;
}

// set number of lives
void Character::setLives(int nrLives) {
	lives += nrLives;
}

// check if it is alive
bool Character::isAlive() {
	if (lives <= 0)
		return false;
	else
		return true;
}