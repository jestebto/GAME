#include "SpriteManager.h"


SpriteManager::SpriteManager()
{
	// Pre-make the map for the tiles.
	// Note: this does not require the actual images or tiles themselves
	//createTileMap(); -> moved to SpriteManager::setSheet
}

SpriteManager::~SpriteManager()
{
	SDL_DestroyTexture(sheetSprites);
}


void SpriteManager::setSheet(SDL_Texture* texture) {
	this->sheetSprites = texture;
	// Pre-make the map for the tiles.
	// Note: this does not require the texture
	createTileMap();
}

SDL_Texture* SpriteManager::getSheet() {
	return this->sheetSprites;
}


/// get a tile on SpriteManager::sheet 
SDL_Rect* SpriteManager::getTile(std::unique_ptr<GameSprite> const& element) {
	return &tileSet.at(element->art).at(element->description); //< &tileSet[art][des] does unwanted behaviour: creates a default element if it can't find the element
}

SDL_Rect* SpriteManager::getTile(SpriteAttributes::ArtType art, SpriteAttributes::Description des) {
	return &tileSet.at(art).at(des); //< &tileSet[art][des] does unwanted behaviour: creates a default element if it can't find the element
}


void SpriteManager::moveSprite(std::unique_ptr<GameSprite> const& element, int x, int y, CharacterOrientation dir)
{
	element->setXPosition(x);
	element->setYPosition(y);
	SpriteAttributes::Description des = SpriteAttributes::mapOrientationToDescription(dir);
	element->setDescription(des);
}

void SpriteManager::moveSprite(std::unique_ptr<GameSprite> const& element, int x, int y)
{
	// move a Sprite to a position

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
		element->description = SpriteAttributes::DOWN;
	}
	else if (y_old > y) //moving UP
	{
		element->description = SpriteAttributes::UP;
	}
	if (x_old < x) //moving right
	{
		element->description = SpriteAttributes::RIGHT;
	}
	else if (x_old > x) //moving left
	{
		element->description = SpriteAttributes::LEFT;
	}

}

void SpriteManager::moveSprite(std::unique_ptr<GameSprite> const& element, UserInputType command)
{
	// directly move a Sprite based on user input
	// for test purposes only, as this is not connected to the logic

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
		element->description = SpriteAttributes::UP; //for display purposes only
		break;
	case UserInputType::Down:
		element->setYPosition(element->getYPosition() + moveSize);
		element->description = SpriteAttributes::DOWN; //for display purposes only
		break;
	case UserInputType::Left:
		element->setXPosition(element->getXPosition() - moveSize);
		element->description = SpriteAttributes::LEFT; //for display purposes only
		break;
	case UserInputType::Right:
		element->setXPosition(element->getXPosition() + moveSize);
		element->description = SpriteAttributes::RIGHT; //for display purposes only
		break;
	default:
		//Do nothing
		break;

	}
}


/// From the Pacman Code
void SpriteManager::createTileMap()
{

	using namespace SpriteAttributes;
	// Declare local enums since using these strong enums a lot
	/*
	enum CharacterOrientation UP = CharacterOrientation::Up;
	enum CharacterOrientation DOWN = CharacterOrientation::Down;
	enum CharacterOrientation LEFT = CharacterOrientation::Left;
	enum CharacterOrientation RIGHT = CharacterOrientation::Right;*/

	const int size = PACMAN_TILESIZE;
	const int o = 4; // offset in bitmap (both in x and y)
	std::map<Description, SDL_Rect> pacman;
	//                    x              y      width,height
	pacman[UP] = { o + size * 1, o + size * 11, size, size };
	pacman[DOWN] = { o + size * 13, o + size * 7, size, size };
	pacman[LEFT] = { o + size * 0, o + size * 11, size, size };
	pacman[RIGHT] = { o + size * 12, o + size * 7, size, size };
	pacman[DEFAULT] = pacman[RIGHT];
	tileSet[PACMAN] = pacman;

	std::map<Description, SDL_Rect> pinky;
	pinky[UP] = { o + size * 6, o + size * 9, size, size };
	pinky[DOWN] = { o + size * 2, o + size * 9, size, size };
	pinky[RIGHT] = { o + size * 0, o + size * 9, size, size };
	pinky[LEFT] = { o + size * 4, o + size * 9, size, size };
	pinky[DEFAULT] = pinky[RIGHT];
	tileSet[PINKY] = pinky;

	std::map<Description, SDL_Rect> blinky;
	blinky[UP] = { o + size * 6, o + size * 7, size, size };
	blinky[DOWN] = { o + size * 2, o + size * 7, size, size };
	blinky[RIGHT] = { o + size * 0, o + size * 7, size, size };
	blinky[LEFT] = { o + size * 4, o + size * 7, size, size };
	blinky[DEFAULT] = blinky[RIGHT];
	tileSet[BLINKY] = blinky;

	std::map<Description, SDL_Rect> clyde;
	clyde[UP] = { o + size * 6, o + size * 10, size, size };
	clyde[DOWN] = { o + size * 2, o + size * 10, size, size };
	clyde[RIGHT] = { o + size * 0, o + size * 10, size, size };
	clyde[LEFT] = { o + size * 4, o + size * 10, size, size };
	clyde[DEFAULT] = clyde[RIGHT];
	tileSet[CLYDE] = clyde;

	std::map<Description, SDL_Rect> inky;
	inky[UP] = { o + size * 14, o + size * 9, size, size };
	inky[DOWN] = { o + size * 10, o + size * 9, size, size };
	inky[LEFT] = { o + size * 12, o + size * 9, size, size };
	inky[RIGHT] = { o + size * 8, o + size * 9, size, size };
	inky[DEFAULT] = inky[RIGHT];
	tileSet[INKY] = inky;

	std::map<Description, SDL_Rect> scared;
	scared[DEFAULT] = { o + size * 12, o + size * 6, size, size };
	tileSet[SCARED] = scared;

	std::map<Description, SDL_Rect> scaredinv;
	scaredinv[DEFAULT] = { o + size * 4, o + size * 11, size, size };
	tileSet[SCAREDINV] = scaredinv;

	std::map<Description, SDL_Rect> strawberry;
	strawberry[DEFAULT] = { o + size * 1, o + size * 5, size, size };
	tileSet[STRAWBERRY] = strawberry;

	std::map<Description, SDL_Rect> cherry;
	cherry[DEFAULT] = { o + size * 0, o + size * 5, size, size };
	tileSet[CHERRY] = cherry;

	std::map<Description, SDL_Rect> orange;
	orange[DEFAULT] = { o + size * 2, o + size * 5, size, size };
	tileSet[ORANGE] = orange;

	std::map<Description, SDL_Rect> lemon;
	lemon[DEFAULT] = { o + size * 3, o + size * 5, size, size };
	tileSet[LEMON] = lemon;

	std::map<Description, SDL_Rect> apple;
	apple[DEFAULT] = { o + size * 4, o + size * 5, size, size };
	tileSet[APPLE] = apple;

	std::map<Description, SDL_Rect> grapes;
	grapes[DEFAULT] = { o + size * 5, o + size * 5, size, size };
	tileSet[GRAPES] = grapes;

	std::map<Description, SDL_Rect> dot;
	dot[DEFAULT] = { o + 12 * 16, o + 12 * 0, size / 2, size / 2 };
	tileSet[DOT] = dot;

	std::map<Description, SDL_Rect> energizer;
	energizer[DEFAULT] = { o + 12 * 18, o + 12 * 0, size / 2, size / 2 };
	tileSet[ENERGIZER] = energizer;

	std::map<Description, SDL_Rect> wall;
	wall[DEFAULT] = { o + size * 6, o + size * 11, size, size };
	tileSet[WALL] = wall;

	std::map<Description, SDL_Rect> key;
	key[DEFAULT] = { o + size * 7, o + size * 5, size, size };
	tileSet[KEY] = key;

	for (int i = 0; i < 10; i++) {
		std::map<Description, SDL_Rect> nr;
		nr[UP] = { o + (size / 2) * i, o + 1 + size * 0, size / 2, size / 2 };
		nr[DOWN] = nr[UP];
		nr[LEFT] = nr[UP];
		nr[RIGHT] = nr[UP];
		tileSet[(ArtType)(ZERO + i)] = nr;
	}
}
