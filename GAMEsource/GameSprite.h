/*
 *  Created on: 28 November, 2018
 *      Author: Lior Sinai
 * Description: Creates a sprite game object for the Graphic user interface.
 * TODO: Inherit from GameObject class (requires making properties public) ????
 */


#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H
#include <string>
#include <iostream>
#include "DataUpdate.h"
#include "CharacterOrientation.h"

/// Define attributes important only for Sprite objects in the graphic user interface 
namespace SpriteAttributes {
	/// Artwork Type used for each sprite 
	 enum ArtType {
		PACMAN,
		BLINKY,
		PINKY,
		INKY,
		CLYDE,
		SCARED,
		SCAREDINV,
		KEY,
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

	 /// Generic descriptions/actions for each sprite
	 enum Description { UP, DOWN, LEFT, RIGHT, DEFAULT, ATTACK, ELIMINATE };

	 /// Map enums of the smaller CharacterOrientation enum class to the bigger Description enum class
    /// Unforunately there is no nice way to inherit enums in C++
	 static Description mapOrientationToDescription(CharacterOrientation Ori) {
		 switch (Ori)
		 {
		 case CharacterOrientation::Up:	   return UP;
		 case CharacterOrientation::Down:  return DOWN;
		 case CharacterOrientation::Left:  return LEFT;
		 case CharacterOrientation::Right: return RIGHT;
		 default: return DEFAULT;
		 }
	 };
	 
}

class GameSprite
{
public:
	GameSprite(DataUpdate::ObjectType, int, int, SpriteAttributes::ArtType, SpriteAttributes::Description);
	~GameSprite(); // vitual destructor

	void setType(SpriteAttributes::ArtType);
	void setDescription(SpriteAttributes::Description);

	/* Shared functions with GameObject */
	//void setID(const std::string&);
	std::string getID();

	void setXPosition(int);
	int getXPosition();

	void setYPosition(int);
	int getYPosition();
	
	SpriteAttributes::ArtType art;
	SpriteAttributes::Description description;

private:
	/* Shared properties with GameObject */
	std::string objectID;
	DataUpdate::ObjectType objectType;
	int xPosition;
	int yPosition;
	

};

#endif // GAME_SPRITE_H