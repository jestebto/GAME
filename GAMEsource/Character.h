#pragma once

#include "GameObject.h"

class Character : public GameObject {
public:
	/// constructor 
	Character(const std::string, int, int, int);
	/// virtual destructor
	virtual ~Character() = default; 
	/// set lives
	void setLives(int);

	/// get lives
	int getLives();

	/// check if the character is alive
	bool isAlive();

	/// save the data in a string
	virtual std::string dataToString();

private:
	int lives; /// number of lives
};

