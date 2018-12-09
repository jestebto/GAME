#include "Player.h"

//constructor
Player::Player(std::string ID, int xPos, int yPos, int lives, int ori) // Added orientation
	:Character(ID, xPos, yPos, lives) {
	orientation = ori;
};

//Get the current orientation
int Player::getR() {
	return orientation; 
}

//Set the desired orientation
void Player::setR(int ori) {
	orientation = ori ;
}

