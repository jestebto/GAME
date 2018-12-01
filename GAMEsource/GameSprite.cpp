/*
 *  Created on: 28 November, 2018
 *      Author: Lior Sinai
 * Description: See GrameSprite.h
 */

#include <string>
#include "GameSprite.h"

GameSprite::GameSprite(std::string ID, int xPos, int yPos, ArtType artType, Direction dir) {
	objectID = ID;
	xPosition = xPos;
	yPosition = yPos;
	art = artType;
	direction = dir;
}

/// set Sprite artwork based on type
void GameSprite::setType(ArtType artType) {
	art = artType;
}

/// set Sprite artwork based on type
void GameSprite::setDirection(Direction dir) {
	direction = dir;
}

/// return object ID
std::string GameSprite::getID() { return objectID; }

/// set X-Position
void GameSprite::setXPosition(int xPos) {
	xPosition = xPos;
}

/// return X-Position
int GameSprite::getXPosition() { return xPosition; }

/// set Y-Position
void GameSprite::setYPosition(int yPos) {
	yPosition = yPos;
}

/// return Y-Position
int GameSprite::getYPosition() { return yPosition; }