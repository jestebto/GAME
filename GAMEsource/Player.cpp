#include "Player.h"

//constructor
Player::Player(std::string ID, int xPos, int yPos, int lives, CharacterOrientation ori, int dmg) // Added orientation
	:Character(ID, xPos, yPos, lives) {
	setR(ori);
	setDmg(dmg);
};

//Get the current orientation
CharacterOrientation Player::getR() {
	return orientation; 
}

//Set the desired orientation
void Player::setR(CharacterOrientation ori) {
	orientation = ori ;
}

//Get the current damage of player
int Player::getDmg() {
	return damage;
}


//Set the desired damage of the player
void Player::setDmg(int dmg) {
	damage = dmg;
}

///return a string with the object's data
std::string Player::dataToString() {
	std::ostringstream addData;
	/*
	addData << this->getID() << "," << this->getXPosition()
		<< "," << this->getYPosition() << ",";
	*/
	addData << this->getLives() << "," << static_cast<int>(this->getR()) << ",";
	std::string totalData = addData.str();
	return totalData;
}
