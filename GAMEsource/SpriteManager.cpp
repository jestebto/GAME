#include "SpriteManager.h"


SpriteManager::SpriteManager(int tileSize)
{
	size = tileSize;
}

SpriteManager::~SpriteManager()
{
	//SDL_DestroyTexture(sheet);
}

/*
void SpriteManager::setSheet() {
	art = artType;
}
*/

void SpriteManager::moveSprite(GameSprite* element, int x, int y)
{
	// move a Sprite to a position
	using namespace SpriteAttributes;

	/*  Co-ordinates:
	*   .---> +x
	*   |
	*   v
	*   +y
	*/

	int x_old = element->getXPosition();
	int y_old = element->getYPosition();

	element->setXPosition(x);
	element->setYPosition(y);
	if (y_old < y) // moving DOWN
	{
		element->direction = DOWN;
	}
	else if (y_old > y) //moving UP
	{
		element->direction = UP;
	}
	if (x_old < x) //moving right
	{
		element->direction = RIGHT;
	}
	else if (x_old > x) //moving left
	{
		element->direction = LEFT;
	}

}

void SpriteManager::moveSprite(GameSprite* element, UserInputType command)
{
	// directly move a Sprite based on user input
	// for test purposes only, as this is not connected to the logic
	using namespace SpriteAttributes;

	int moveSize = 1;
	/*  Co-ordinates:
	*   .---> +x
	*   |
	*   v
	*   +y
	*/


	switch (command) {
	case UserInputType::Up:
		element->setYPosition(element->getYPosition() - moveSize);
		element->direction = UP; //for display purposes only
		break;
	case UserInputType::Down:
		element->setYPosition(element->getYPosition() + moveSize);
		element->direction = DOWN; //for display purposes only
		break;
	case UserInputType::Left:
		element->setXPosition(element->getXPosition() - moveSize);
		element->direction = LEFT; //for display purposes only
		break;
	case UserInputType::Right:
		element->setXPosition(element->getXPosition() + moveSize);
		element->direction = RIGHT; //for display purposes only
		break;
	default:
		//Do nothing
		break;

	}
}

