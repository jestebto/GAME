#ifndef POWERUP_H
#define POWERUP_H

#include "GameObject.h"

class PowerUp : public GameObject {
public:
	PowerUp(const std::string, int, int, int);

	//set the number of lives to be given
	void setNrOfLives(int);

	//return number of lives that the power-up gives
	int getNrOfLives();

private:
	int nrOfLives;
};
#endif // !POWERUP_H
