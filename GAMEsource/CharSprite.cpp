#include "CharSprite.h"



CharSprite::CharSprite(DataUpdate::ObjectType objectType, int xPos, int yPos, 
	SpriteAttributes::ArtType artType, SpriteAttributes::Description des, CharacterOrientation ori)
	: GameSprite(objectType, xPos, yPos, artType, des)
{
	orientation = ori;
}


CharSprite::~CharSprite()
{
}

/// set Sprite artwork based on type
void CharSprite::setOrientation(CharacterOrientation newOrientation) {
	this->orientation = newOrientation;
}

/// get Sprite artwork
CharacterOrientation CharSprite::getOrientation() {
	return this->orientation;
}

void CharSprite::moveSprite(int x, int y)
{
	setXPosition(x);
	setYPosition(y);
	SpriteAttributes::Description des = CharSprite::mapOrientationToDescription(this->orientation);
	setDescription(des);
}
