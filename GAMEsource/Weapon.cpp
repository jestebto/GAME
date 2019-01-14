#include "Weapon.h"



Weapon::Weapon(std::string ID, int xPos, int yPos,
	int nrLives, int damage)
	: GameObject(ID, xPos, yPos) {
	if (damage < 0) throw std::invalid_argument("The damage of the weapon must be a positive integer.");
	damageValue = damage;
};


// return damage value
int Weapon::getDamage() const { return damageValue; }