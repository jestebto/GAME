#pragma once


#ifndef CHAR_SPRITE_H
#define CHAR_SPRITE_H

#include "GameSprite.h"

class CharSprite : public GameSprite
{
public:
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

	void moveSprite(int, int); //< get all information from the logic manager

private:
	CharacterOrientation orientation;
};


#endif // CHAR_SPRITE_H
