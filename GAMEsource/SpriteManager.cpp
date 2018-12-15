#include "SpriteManager.h"


SpriteManager::SpriteManager()
{
	// Pre-make the map for the tiles.
	// Note: this does not require the actual images or tiles themselves!!
	//createTileMap();
}

SpriteManager::~SpriteManager()
{
	SDL_DestroyTexture(sheetSprites);
}


void SpriteManager::setSheet(SDL_Texture* texture) {
	this->sheetSprites = texture;
	createTileMap();
}

SDL_Texture* SpriteManager::getSheet() {
	return this->sheetSprites;
}


/// get a tile on SpriteManager::sheet 
SDL_Rect* SpriteManager::getTile(std::unique_ptr<GameSprite> const& element) {
	return &tileSet[element->art][element->direction];
}

SDL_Rect* SpriteManager::getTile(SpriteAttributes::ArtType art, CharacterOrientation dir) {
	return &tileSet[art][dir];
}


void SpriteManager::moveSprite(std::unique_ptr<GameSprite> const& element, int x, int y)
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
		element->direction = CharacterOrientation::Down;
	}
	else if (y_old > y) //moving UP
	{
		element->direction = CharacterOrientation::Up;
	}
	if (x_old < x) //moving right
	{
		element->direction = CharacterOrientation::Right;
	}
	else if (x_old > x) //moving left
	{
		element->direction = CharacterOrientation::Left;
	}

}

void SpriteManager::moveSprite(std::unique_ptr<GameSprite> const& element, int x, int y, CharacterOrientation dir)
{
	element->setXPosition(x);
	element->setYPosition(y);
	element->setDirection(dir);
}

void SpriteManager::moveSprite(std::unique_ptr<GameSprite> const& element, UserInputType command)
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
		element->direction = CharacterOrientation::Up; //for display purposes only
		break;
	case UserInputType::Down:
		element->setYPosition(element->getYPosition() + moveSize);
		element->direction = CharacterOrientation::Down; //for display purposes only
		break;
	case UserInputType::Left:
		element->setXPosition(element->getXPosition() - moveSize);
		element->direction = CharacterOrientation::Left; //for display purposes only
		break;
	case UserInputType::Right:
		element->setXPosition(element->getXPosition() + moveSize);
		element->direction = CharacterOrientation::Right; //for display purposes only
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
	enum CharacterOrientation UP = CharacterOrientation::Up;
	enum CharacterOrientation DOWN = CharacterOrientation::Down;
	enum CharacterOrientation LEFT = CharacterOrientation::Left;
	enum CharacterOrientation RIGHT = CharacterOrientation::Right;

	const int size = PACMAN_TILESIZE;
	const int o = 4; // offset in bitmap (both in x and y)
	std::map<CharacterOrientation, SDL_Rect> pacman;
	//                    x              y      width,height
	pacman[UP] = { o + size * 1, o + size * 11, size, size };
	pacman[DOWN] = { o + size * 13, o + size * 7, size, size };
	pacman[LEFT] = { o + size * 0, o + size * 11, size, size };
	pacman[RIGHT] = { o + size * 12, o + size * 7, size, size };
	tileSet[PACMAN] = pacman;

	std::map<CharacterOrientation, SDL_Rect> pinky;
	pinky[UP] = { o + size * 6, o + size * 9, size, size };
	pinky[DOWN] = { o + size * 2, o + size * 9, size, size };
	pinky[RIGHT] = { o + size * 0, o + size * 9, size, size };
	pinky[LEFT] = { o + size * 4, o + size * 9, size, size };
	tileSet[PINKY] = pinky;

	std::map<CharacterOrientation, SDL_Rect> blinky;
	blinky[UP] = { o + size * 6, o + size * 7, size, size };
	blinky[DOWN] = { o + size * 2, o + size * 7, size, size };
	blinky[RIGHT] = { o + size * 0, o + size * 7, size, size };
	blinky[LEFT] = { o + size * 4, o + size * 7, size, size };
	tileSet[BLINKY] = blinky;

	std::map<CharacterOrientation, SDL_Rect> clyde;
	clyde[UP] = { o + size * 6, o + size * 10, size, size };
	clyde[DOWN] = { o + size * 2, o + size * 10, size, size };
	clyde[RIGHT] = { o + size * 0, o + size * 10, size, size };
	clyde[LEFT] = { o + size * 4, o + size * 10, size, size };
	tileSet[CLYDE] = clyde;

	std::map<CharacterOrientation, SDL_Rect> inky;
	inky[UP] = { o + size * 14, o + size * 9, size, size };
	inky[DOWN] = { o + size * 10, o + size * 9, size, size };
	inky[LEFT] = { o + size * 12, o + size * 9, size, size };
	inky[RIGHT] = { o + size * 8, o + size * 9, size, size };
	tileSet[INKY] = inky;

	std::map<CharacterOrientation, SDL_Rect> scared;
	scared[UP] = { o + size * 12, o + size * 6, size, size };
	scared[DOWN] = scared[UP];
	scared[LEFT] = scared[UP];
	scared[RIGHT] = scared[UP];
	tileSet[SCARED] = scared;

	std::map<CharacterOrientation, SDL_Rect> scaredinv;
	scaredinv[UP] = { o + size * 4, o + size * 11, size, size };
	scaredinv[DOWN] = scaredinv[UP];
	scaredinv[LEFT] = scaredinv[UP];
	scaredinv[RIGHT] = scaredinv[UP];
	tileSet[SCAREDINV] = scaredinv;

	std::map<CharacterOrientation, SDL_Rect> strawberry;
	strawberry[UP] = { o + size * 1, o + size * 5, size, size };
	strawberry[DOWN] = strawberry[UP];
	strawberry[LEFT] = strawberry[UP];
	strawberry[RIGHT] = strawberry[UP];
	tileSet[STRAWBERRY] = strawberry;

	std::map<CharacterOrientation, SDL_Rect> cherry;
	cherry[UP] = { o + size * 0, o + size * 5, size, size };
	cherry[DOWN] = cherry[UP];
	cherry[LEFT] = cherry[UP];
	cherry[RIGHT] = cherry[UP];
	tileSet[CHERRY] = cherry;

	std::map<CharacterOrientation, SDL_Rect> orange;
	orange[UP] = { o + size * 2, o + size * 5, size, size };
	orange[DOWN] = orange[UP];
	orange[LEFT] = orange[UP];
	orange[RIGHT] = orange[UP];
	tileSet[ORANGE] = orange;

	std::map<CharacterOrientation, SDL_Rect> lemon;
	lemon[UP] = { o + size * 3, o + size * 5, size, size };
	lemon[DOWN] = lemon[UP];
	lemon[LEFT] = lemon[UP];
	lemon[RIGHT] = lemon[UP];
	tileSet[LEMON] = lemon;

	std::map<CharacterOrientation, SDL_Rect> apple;
	apple[UP] = { o + size * 4, o + size * 5, size, size };
	apple[DOWN] = apple[UP];
	apple[LEFT] = apple[UP];
	apple[RIGHT] = apple[UP];
	tileSet[APPLE] = apple;

	std::map<CharacterOrientation, SDL_Rect> grapes;
	grapes[UP] = { o + size * 5, o + size * 5, size, size };
	grapes[DOWN] = grapes[UP];
	grapes[LEFT] = grapes[UP];
	grapes[RIGHT] = grapes[UP];
	tileSet[GRAPES] = grapes;

	std::map<CharacterOrientation, SDL_Rect> dot;
	dot[UP] = { o + 12 * 16, o + 12 * 0, size / 2, size / 2 };
	dot[DOWN] = dot[UP];
	dot[LEFT] = dot[UP];
	dot[RIGHT] = dot[UP];
	tileSet[DOT] = dot;

	std::map<CharacterOrientation, SDL_Rect> energizer;
	energizer[UP] = { o + 12 * 18, o + 12 * 0, size / 2, size / 2 };
	energizer[DOWN] = energizer[UP];
	energizer[LEFT] = energizer[UP];
	energizer[RIGHT] = energizer[UP];
	tileSet[ENERGIZER] = energizer;

	std::map<CharacterOrientation, SDL_Rect> wall;
	wall[UP] = { o + size * 6, o + size * 11, size, size };
	wall[DOWN] = wall[UP];
	wall[LEFT] = wall[UP];
	wall[RIGHT] = wall[UP];
	tileSet[WALL] = wall;

	std::map<CharacterOrientation, SDL_Rect> key;
	key[UP] = { o + size * 7, o + size * 5, size, size };
	key[DOWN] = key[UP];
	key[LEFT] = key[UP];
	key[RIGHT] = key[UP];
	tileSet[KEY] = key;

	for (int i = 0; i < 10; i++) {
		std::map<CharacterOrientation, SDL_Rect> nr;
		nr[UP] = { o + (size / 2) * i, o + 1 + size * 0, size / 2, size / 2 };
		nr[DOWN] = nr[UP];
		nr[LEFT] = nr[UP];
		nr[RIGHT] = nr[UP];
		tileSet[(ArtType)(ZERO + i)] = nr;
	}
}
