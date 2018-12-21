#pragma once

#include <string>
#include <sstream>

/// A generic game object that can be moved around. Used in the logic component. Compare GameSprite.
class GameObject {
public:
	/// constructor
	GameObject(std::string, int, int);
	/// vitual destructor
	virtual ~GameObject() = default; 

	/// get object ID
	std::string getID();

	/// set x-position
	void setXPosition(int);

	/// get x-position
	int getXPosition();

	/// set y-position
	void setYPosition(int);
	/// get y-position
	int getYPosition();

	/// save the data in a string
	virtual std::string dataToString();

private:
	std::string objectID; /// objects ID
	int xPosition;/// x-position
	int yPosition; /// y-position

};

