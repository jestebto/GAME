#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

class Character : public GameObject {
public:
	Character(const std::string, int, int, int);
	virtual ~Character() = default; //virtual destructor

	void setLives(int);

	bool isAlive();

private:
	int lives; /// number of lives
};

#endif // CHARACTER_H