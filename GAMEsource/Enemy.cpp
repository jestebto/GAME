#include "Enemy.h"

Enemy::Enemy(std::string ID, int xPos, int yPos,
	int nrLives, int damage)
	: Character(ID, xPos, yPos, nrLives) {
	damageValue = damage;
};


/// return damage value
int Enemy::getDamage() const { return damageValue; }