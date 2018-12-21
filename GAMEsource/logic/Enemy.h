#pragma once

#include "Character.h"

class Enemy : public Character {
public:
	// input: ID,XPOS,YPOS,LIVES,DAMAGE
	/// constructor
	Enemy(std::string, int, int, int, const int);

	/// destructor
	virtual ~Enemy() = default; // virtual destructor

	/// get the damage 
	int getDamage() const; 

private:
	int damageValue;  /// damage to player 
};

