#include "Enemy.h"

Enemy::Enemy(std::string ID, int xPos, int yPos,
	int nrLives, int damage)
	: Character(ID, xPos, yPos, nrLives) {
	if (damage < 0) throw "The damage of the enemy must be a positive integer.";
	damageValue = damage;
};


/// return damage value
int Enemy::getDamage() const { return damageValue; }