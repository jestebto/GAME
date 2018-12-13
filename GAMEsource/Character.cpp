#include "Character.h"

// constructor
Character::Character(const std::string ID, int xPos, int yPos,
	int nrLives)
	: GameObject(ID, xPos, yPos) {
	lives = nrLives;
}

/// set number of lives
void Character::setLives(int nrLives) {
	lives += nrLives;
}

int Character::getLives() {
	return lives;
}

// check if it is alive

bool Character::isAlive() {
	if (lives <= 0)
		return false;
	else
		return true;
}

///return a string with the object's data
std::string Character::dataToString() {
	std::ostringstream addData;
	/*
	addData << this->getID() << "," << this->getXPosition()
		<< "," << this->getYPosition() << ",";
	*/
	addData << this->getLives() << ",";
	std::string totalData = addData.str();
	return totalData;
}