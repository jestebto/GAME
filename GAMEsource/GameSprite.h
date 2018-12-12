/*
 *  Created on: 28 November, 2018
 *      Author: Lior Sinai
 * Description: Creates a sprite game object for the Graphic user interface.
 * TODO: Inherit from GameObject class (requires making properties public) ????
 */


#ifndef GAME_SPRITE_H
#define GAME_SPRITE_H
#include <string>

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

	/// The direction a sprite faces
	enum Direction { UP, DOWN, LEFT, RIGHT };
}

class GameSprite
{
public:
	GameSprite(std::string, int, int, SpriteAttributes::ArtType, SpriteAttributes::Direction);
	virtual ~GameSprite() = default; // vitual destructor

	void setType(SpriteAttributes::ArtType);
	void setDirection(SpriteAttributes::Direction);

	/* Shared functions with GameObject */
	//void setID(const std::string&);
	std::string getID();

	void setXPosition(int);
	int getXPosition();

	void setYPosition(int);
	int getYPosition();
	
	SpriteAttributes::ArtType art;
	SpriteAttributes::Direction direction;

private:
	/* Shared properties with GameObject */
	std::string objectID;
	int xPosition;
	int yPosition;
	

};

#endif // GAME_SPRITE_H