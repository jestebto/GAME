#pragma once

#include "Character.h"
#include "CharacterOrientation.h"

class Player : public Character {
public:
	Player(std::string, int, int, int, CharacterOrientation, int); //Added one more int for orientation and another for damage total 5 ints and a string
	virtual ~Player() = default;

	CharacterOrientation getR(); //Get current orientation 
	void setR(CharacterOrientation); //Set the orientation 

	// Get the damage
	int getDmg();

	//Set the damage
	void setDmg(int);

	//save the data in a string
	std::string dataToString();

private:
	CharacterOrientation orientation;
	int damage;
};
