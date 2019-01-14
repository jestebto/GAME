#include "Weapon.h"

Weapon ::Weapon(std::string ID, int xPos, int yPos,
	int damage)
	: GameObject(ID, xPos, yPos) {
	if (damage < 0) throw std::exception("The damage of the weapon must be a positive integer.");
	damageValue = damage;
};


/// return damage value of the weapon
int Weapon::getDamage() const { return damageValue; }