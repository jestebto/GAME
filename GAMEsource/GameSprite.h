/*
 *  Created on: 28 November, 2018
 *      Author: Lior Sinai
 * Description: Creates a sprite game object for the Graphic user interface.
 * TODO: Inherit from GameObject class (requires making properties public) ????
 */


#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H
#include <string>
#include "GameObject.h"

/// These enum values denote the sprite sets available for items on screen.
enum Type {
	PACMAN,
	BLINKY,
	PINKY,
	INKY,
	CLYDE,
	SCARED,
	SCAREDINV,
	CHERRY,
	STRAWBERRY,
	ORANGE,
	LEMON,
	APPLE,
	GRAPES,
	DOT,
	ENERGIZER,
	WALL,
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVEN,
	EIGHT,
	NINE
};

/// An enum to denote the direction of an item on screen.
enum Direction { UP, DOWN, LEFT, RIGHT };

//note: enums need to be declared outside the class to be used elsewehre

class GameSprite
{
public:
	GameSprite(std::string, int, int, Type, Direction);
	virtual ~GameSprite() = default; // vitual destructor

	void setType(Type);
	void setDirection(Direction);

	/* Shared functions with GameObject */
	//void setID(const std::string&);
	std::string getID();

	void setXPosition(int&);
	int getXPosition();

	void setYPosition(int&);
	int getYPosition();
	
	Type type;
	Direction direction;

private:
	/* Shared properties with GameObject */
	std::string objectID;
	int xPosition;
	int yPosition;
	

};

#endif // GAMEOBJECT_H