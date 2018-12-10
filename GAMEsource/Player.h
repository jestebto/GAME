#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
public:
	Player(std::string, int, int, int, int, int); //Added one more int for orientation and another for damage total 5 ints and a string
	virtual ~Player() = default;

	int getR();
	void setR(int);

	int getDmg();
	void setDmg(int);

private:
	int orientation;
	int damage;
};
#endif // !PLAYER_H