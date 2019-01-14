#pragma once

#include "GameObject.h"

class Weapon : public GameObject {
public:
	// input: ID,XPOS,YPOS,DAMAGE
	Weapon(std::string, int, int, const int);
	virtual ~Weapon() = default; // virtual destructor

	int getDamage() const; // get the damage 

private:
	int damageValue;  /// damage added 
};

class Weapon
{
public:
	Weapon();
	~Weapon();
};
