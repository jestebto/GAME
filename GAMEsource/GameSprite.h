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
//#include "DataUpdate.h"
#include "UserInputType.h"
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

	 /// For descriptions/actions for each artwork
	 enum Description { UP, DOWN, LEFT, RIGHT, DEFAULT, ALT, 
		              ATTACK_UP, ATTACK_DOWN, ATTACK_LEFT, ATTACK_RIGHT,
		              ELIMINATE };
 
}

class GameSprite
{
public:
	GameSprite(int, int, SpriteAttributes::ArtType, SpriteAttributes::Description);
	~GameSprite(); // vitual destructor

	void setType(SpriteAttributes::ArtType); ///< set sprite artwork
	SpriteAttributes::ArtType getArt(); ///< get sprite artwork

	void setDescription(SpriteAttributes::Description); ///< set sprite artwork description
	SpriteAttributes::Description getDescription(); ///< get sprite artwork description

	virtual void moveSprite(int, int); ///< Estimate direction using the new and old co-ordinates
	void moveSprite(UserInputType); ///< For test purposes only, as this is not connected to the logic

	
	virtual void setOrientation(CharacterOrientation); ///< Define virtual functions for use with more complex GameSprite child classes
	virtual CharacterOrientation getOrientation(); ///< Return CharacterOrientation::None

	/* Shared functions with GameObject */
	//void setID(const std::string&);
	std::string getID(); ///< a unique a ID shared with a GameObject in the logic side

	void setXPosition(int); ///< set X-Position
	int getXPosition(); ///< get X-Position

	void setYPosition(int); ///< get Y-Position
	int getYPosition(); ///< get Y-Position
	
private:
	SpriteAttributes::ArtType art;
	SpriteAttributes::Description description;
	/* Shared properties with GameObject */
	std::string objectID;
	//DataUpdate::ObjectType objectType;
	int xPosition;
	int yPosition;


};

#endif // GAME_SPRITE_H