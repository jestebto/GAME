#include "CharSprite.h"



CharSprite::CharSprite( int xPos, int yPos, SpriteAttributes::ArtType artType, 
	SpriteAttributes::Description des, CharacterOrientation ori)
	: GameSprite(xPos, yPos, artType, des)
{
	orientation = ori;
}


CharSprite::~CharSprite()
{
}

void CharSprite::setOrientation(CharacterOrientation newOrientation) {
	this->orientation = newOrientation;
}

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
