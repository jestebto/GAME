#pragma once


#ifndef CHAR_SPRITE_H
#define CHAR_SPRITE_H

#include "GameSprite.h"

class CharSprite : public GameSprite
{
public:
	/// A more complex GameSprite that can handle orientations
	/// This is important for playing animations in the right direction
	CharSprite(DataUpdate::ObjectType objectType, int xPos, int yPos, 
		SpriteAttributes::ArtType artType, SpriteAttributes::Description des, CharacterOrientation ori);
	~CharSprite();

	void setOrientation(CharacterOrientation);
	CharacterOrientation getOrientation();

	/// Map enums of the smaller CharacterOrientation enum class to the bigger Description enum class
	/// Unforunately there is no nice way to inherit enums in C++
	static SpriteAttributes::Description mapOrientationToDescription(CharacterOrientation Ori) {
		switch (Ori)
		{
		case CharacterOrientation::Up:	  return SpriteAttributes::UP;
		case CharacterOrientation::Down:  return SpriteAttributes::DOWN;
		case CharacterOrientation::Left:  return SpriteAttributes::LEFT;
		case CharacterOrientation::Right: return SpriteAttributes::RIGHT;
		default: return SpriteAttributes::DEFAULT;
		}
	};

	/// Override virtual function in GameSprite
	void moveSprite(int, int); //<  uses the current CharSprite::orientation 

private:
	CharacterOrientation orientation;
};


#endif // CHAR_SPRITE_H
