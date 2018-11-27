#include <string>
#include "GameObject.h"

GameObject::GameObject(std::string ID, int xPos, int yPos) {
	objectID = ID;
	xPosition = xPos;
	yPosition = yPos;
}


// return object ID
std::string GameObject::getID() { return objectID; }

// set X-Position
void GameObject::setXPosition(int& xPos) {
	xPosition = xPos;
}

// return X-Position
int GameObject::getXPosition() { return xPosition; }

// set Y-Position
void GameObject::setYPosition(int& yPos) {
	yPosition = yPos;
}

// return Y-Position
int GameObject::getYPosition() { return yPosition; }