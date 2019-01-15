/*
 *  Created on: 28 November, 2018
 *      Author: Lior Sinai
 * Description: See GrameSprite.h
 */


#include "GameSprite.h"

GameSprite::GameSprite(int xPos, int yPos, SpriteAttributes::ArtType artType, SpriteAttributes::Description des, SpriteAttributes::TileType select) {
	//objectID = ID;
	//objectType = objectType;
	xPosition = xPos;
	yPosition = yPos;
	art = artType;
	description = des;
	tm = select;
}

GameSprite::~GameSprite() {
	//std::cout << "destroy" << '\n';
}

// set Sprite artwork based on type
void GameSprite::setType(SpriteAttributes::ArtType artType) {
	art = artType;
}

// get Sprite artwork
SpriteAttributes::ArtType GameSprite::getArt() {
	return this->art;
}

// set Sprite artwork description
void GameSprite::setDescription(SpriteAttributes::Description des) {
	description = des;
}

// get Sprite artwork description
SpriteAttributes::Description GameSprite::getDescription() {
	return this->description;
}

// return object ID
//std::string GameSprite::getID() { return objectID; }

// set X-Position
void GameSprite::setXPosition(int xPos) {
	xPosition = xPos;
}

// return X-Position
int GameSprite::getXPosition() { return xPosition; }

// set Y-Position
void GameSprite::setYPosition(int yPos) {
	yPosition = yPos;
}

// return Y-Position
int GameSprite::getYPosition() { return yPosition; }

// Move sprite and estimate orienation
void GameSprite::moveSprite(int x, int y)
{
	// move a Sprite to a position

	/*  Co-ordinates:
	*   .---> +x
	*   |
	*   v
	*   +y
	*/

	int x_old = getXPosition();
	int y_old = getYPosition();

	setXPosition(x);
	setYPosition(y);
	/* //From earlier version where this was used to estimate the direction
	if (y_old < y) // moving DOWN
	{
		description = SpriteAttributes::DOWN;
	}
	else if (y_old > y) //moving UP
	{
		description = SpriteAttributes::UP;
	}
	if (x_old < x) //moving right
	{
		description = SpriteAttributes::RIGHT;
	}
	else if (x_old > x) //moving left
	{
		description = SpriteAttributes::LEFT;
	}
	*/
}

void GameSprite::moveSprite(int value)
{
	// don't move it all all
}

void GameSprite::moveSprite(UserInputType command, int moveSize)
{
	// directly move a Sprite based on user input
	// for test purposes only, as this is not connected to the logic

	/*  Co-ordinates:
	*   .---> +x
	*   |
	*   v
	*   +y
	*/

	switch (command) {
	case UserInputType::Up:
		setYPosition(getYPosition() - moveSize);
		description = SpriteAttributes::UP; //for display purposes only
		break;
	case UserInputType::Down:
		setYPosition(getYPosition() + moveSize);
		description = SpriteAttributes::DOWN; //for display purposes only
		break;
	case UserInputType::Left:
		setXPosition(getXPosition() - moveSize);
		description = SpriteAttributes::LEFT; //for display purposes only
		break;
	case UserInputType::Right:
		setXPosition(getXPosition() + moveSize);
		description = SpriteAttributes::RIGHT; //for display purposes only
		break;
	default:
		//Do nothing
		break;

	}
}

void GameSprite::setOrientation(CharacterOrientation) {
	//do nothing
};

CharacterOrientation GameSprite::getOrientation(){
	return CharacterOrientation::None;
}