#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
public:
	Player(std::string, int, int, int, int); //Added one more int for orientation
	virtual ~Player() = default;

	int getR();
	void setR(int);

private:
	int orientation;
};
#endif // !PLAYER_H