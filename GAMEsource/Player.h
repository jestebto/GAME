#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "CharacterOrientation.h"

class Player : public Character {
public:
	Player(std::string, int, int, int, CharacterOrientation, int); //Added one more int for orientation and another for damage total 5 ints and a string
	virtual ~Player() = default;

	CharacterOrientation getR(); //More descriptive names
	void setR(CharacterOrientation); //.....

	int getDmg();

	void setDmg(int);

	//save the data in a string
	std::string dataToString();

private:
	CharacterOrientation orientation;
	int damage;
};
#endif // !PLAYER_H