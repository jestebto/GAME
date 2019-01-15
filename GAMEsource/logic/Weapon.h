#pragma once

#include "GameObject.h"
/// A GameObject that increases the damage the player inflicts on enemies
class Weapon : public GameObject {
public:
	// input: ID,XPOS,YPOS,DAMAGE
	Weapon(std::string, int, int, const int);
	virtual ~Weapon() = default; ///< virtual destructor

	int getDamage() const; ///< get the damage 

private:
	int damageValue;  ///< damage added 
};

