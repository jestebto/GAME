#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <string>

class GameObject {
public:

	GameObject(std::string, int, int);
	virtual ~GameObject() = default; // vitual destructor

	//void setID(const std::string&);
	std::string getID();

	void setXPosition(int&);
	int getXPosition();

	void setYPosition(int&);
	int getYPosition();

	//save the data in a string
	std::string dataToString();

private:
	std::string objectID;
	int xPosition;
	int yPosition;

};

#endif // GAMEOBJECT_H