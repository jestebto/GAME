#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
public:
	// input: ID,XPOS,YPOS,LIVES,DAMAGE
	Enemy(std::string, int, int, int, const int);
	virtual ~Enemy() = default; // virtual destructor

	int getDamage() const; // get the damage 

private:
	int damageValue;  //damage to player 
};

#endif // ENEMY_H