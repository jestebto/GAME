#include "Character.h"

// constructor
Character::Character(const std::string ID, int xPos, int yPos,
	int nrLives)
	: GameObject(ID, xPos, yPos) {
	if (nrLives < 0) throw std::invalid_argument("Negative number of lives not possible on creation of the Character object."); //TO DO JOSE: cath in gamemanager and show screen
	lives = nrLives;
}

// ADD a number of lives
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

/// set lives
void Character::setWeapon(std::string weaponID) {
	Character::EQUIPPED = true ;
	Character::weaponID = weaponID;
}

/// get weapon
std::string Character::getWeapon() {
	if (Character::EQUIPPED == true){
		return this->weaponID;
	}
	else {
		return "0";
	}
}

/// drop weapon
void Character::dropWeapon() {
	Character::EQUIPPED = false ;
	this->weaponID = "0";
}

//return a string with the object's data
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