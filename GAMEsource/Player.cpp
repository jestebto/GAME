#include "Player.h"

//constructor
Player::Player(std::string ID, int xPos, int yPos, int lives, int ori, int dmg) // Added orientation
	:Character(ID, xPos, yPos, lives) {
	setR(ori);
	setDmg(dmg);
};

//Get the current orientation
int Player::getR() {
	return orientation; 
}

//Set the desired orientation
void Player::setR(int ori) {
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
