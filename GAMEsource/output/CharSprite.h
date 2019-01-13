#ifndef CHAR_SPRITE_H
#define CHAR_SPRITE_H

#include "GameSprite.h"

/// A more complex GameSprite that can handle orientations.
/// This is important for playing animations in the right direction
class CharSprite : public GameSprite
{
public:
	CharSprite(int xPos, int yPos, SpriteAttributes::ArtType artType, SpriteAttributes::Description des, int, CharacterOrientation ori);
	~CharSprite();

	void setOrientation(CharacterOrientation); 	///< Override virtual function in GameSprite
	CharacterOrientation getOrientation(); ///< Override virtual function in GameSprite

	/// Map enums of the smaller CharacterOrientation enum class to the bigger Description enum class.
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

	/// Override virtual function in GameSprite, so that the artwork is change to match the orientation
	void moveSprite(int, int); 
	void moveSprite(int); ///< move Sprite based on the current orientation

private:
	CharacterOrientation orientation;
};


#endif // CHAR_SPRITE_H
