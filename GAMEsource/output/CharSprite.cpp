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

void CharSprite::moveSprite(int value)
{
	CharacterOrientation ori = this->getOrientation();

	int x = this->getXPosition();
	int y = this->getYPosition();

	switch (ori) {
	case CharacterOrientation::Up: 
		setYPosition(y-value);
		break;
	case CharacterOrientation::Down:
		setYPosition(y+value);
		break;
	case CharacterOrientation::Left:
		setXPosition(x - value);
		break;
	case CharacterOrientation::Right:
		setXPosition(x + value);
		break;
	default:
		break;
	}
	SpriteAttributes::Description des = CharSprite::mapOrientationToDescription(this->orientation);
	setDescription(des);
}
