#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

class Player : public Character {
public:
	Player(std::string, int, int, int);
	virtual ~Player() = default;

};
#endif // !PLAYER_H