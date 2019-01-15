#ifndef CHARACTER_H
#define CHARACTER_H

#include "GameObject.h"

/// A generic class for objects that correspond to moving characters that can interact with their enviornment
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

	/// set weapon
	void setWeapon(std::string);

	/// get weapon. Returns a weapon ID
	std::string getWeapon();

	/// throw weapon
	void dropWeapon();

private:
	int lives; /// number of lives
	std::string weaponID;
	bool EQUIPPED = false ; //Whether the player holds a weapon
};

#endif /* CHARACTER_H */