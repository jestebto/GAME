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
	// Pre-make the animation frame for the tiles.
	createAnimationSequences();
}

SDL_Texture* SpriteManager::getSheet() {
	return this->sheetSprites;
}


SDL_Rect* SpriteManager::getTile(std::unique_ptr<GameSprite> const& element) {
	return &tileSet.at(element->getArt()).at(element->getDescription()); // &tileSet[art][des] does unwanted behaviour: creates a default element if it can't find the element
}

SDL_Rect* SpriteManager::getTile(SpriteAttributes::ArtType art, SpriteAttributes::Description des) {
	return &tileSet.at(art).at(des); // &tileSet[art][des] does unwanted behaviour: creates a default element if it can't find the element
}


std::vector<AnimationTerms::AnimationFrame>* SpriteManager::getAnimationFrames(std::unique_ptr<GameSprite> const& element, SpriteAttributes::ArtType type, AnimationTerms::AnimationTypes action){
	switch (type) {
	case(SpriteAttributes::ArtType::PACMAN): {
		// Note: if this is not a CharSprite, then getOrientation() will return type 'none'
		return &(this->animationsPlayer.at(element->getOrientation()).at(action));
		}
	default: {
		return &(this->animationsOther.at(type).at(action));
	}
	}
}

/// From the Pacman Code
void SpriteManager::createTileMap()
{

	using namespace SpriteAttributes;

	const int size = PACMAN_TILESIZE;
	const int o = 4; // offset in bitmap (both in x and y)
	std::map<Description, SDL_Rect> pacman;
	//                    x              y      width,height
	pacman[UP] = { o + size * 1, o + size * 11, size, size };
	pacman[DOWN] = { o + size * 13, o + size * 7, size, size };
	pacman[LEFT] = { o + size * 0, o + size * 11, size, size };
	pacman[RIGHT] = { o + size * 12, o + size * 7, size, size };
	pacman[ALT] = { o + size * 0, o + size * 8, size, size };
	pacman[ATTACK_UP] =   { o + size * 3, o + size * 11, size, size };
	pacman[ATTACK_DOWN] = { o + size * 15, o + size * 7, size, size };
	pacman[ATTACK_LEFT] = { o + size * 2, o + size * 11, size, size };
	pacman[ATTACK_RIGHT] = { o + size * 14, o + size * 7, size, size };
	pacman[ELIMINATE] = { o + size * 14, o + size * 8, size, size };
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
	scared[ELIMINATE] = { o + size * 1, o + size * 8, size, size };
	tileSet[SCARED] = scared;

	std::map<Description, SDL_Rect> scaredinv;
	scaredinv[DEFAULT] = { o + size * 4, o + size * 11, size, size };
	scaredinv[ELIMINATE] = { o + size * 1, o + size * 8, size, size };
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


void SpriteManager::createAnimationSequences() {
	using namespace SpriteAttributes;
	using namespace AnimationTerms;
	
	/*Create local enums for the strongly typed enums in DataUpdate 
	* This makes it easier to call them so much 
	*/
	/* 
	*DataUpdate::Action nothing = DataUpdate::Action::NOTHING;
	*DataUpdate::Action attack = DataUpdate::Action::ATTACK;
	*DataUpdate::Action eliminate = DataUpdate::Action::ELIMINATE;

	DataUpdate::ObjectType player = DataUpdate::ObjectType::PLAYER;
	DataUpdate::ObjectType enemy = DataUpdate::ObjectType::ENEMY;
	DataUpdate::ObjectType powerUp = DataUpdate::ObjectType::POWERUP;
	*/

	// Set the animations in animationsOther

	std::map<AnimationTypes, std::vector<AnimationFrame>> enemyAnimations;
	enemyAnimations[DIE]= std::vector<AnimationFrame>{
		std::make_pair(SCARED, DEFAULT), std::make_pair(SCARED, ELIMINATE) };
	animationsOther[SCARED] = enemyAnimations;


	// Player animations
	std::map<AnimationTypes, std::vector<AnimationFrame>> playerUpAnimations;
	playerUpAnimations[AnimationTerms::ATTACK]= std::vector<AnimationFrame>{
		std::make_pair(PACMAN, ATTACK_UP), std::make_pair(PACMAN, ALT),
		std::make_pair(PACMAN, ATTACK_UP), std::make_pair(PACMAN, UP)
	};
	animationsPlayer[CharacterOrientation::Up] = playerUpAnimations;

	std::map<AnimationTypes, std::vector<AnimationFrame>> playerDownAnimations;
	playerDownAnimations[AnimationTerms::ATTACK] = std::vector<AnimationFrame>{
		std::make_pair(PACMAN, ATTACK_DOWN), std::make_pair(PACMAN, ALT),
		std::make_pair(PACMAN, ATTACK_DOWN), std::make_pair(PACMAN, DOWN)
	};
	animationsPlayer[CharacterOrientation::Down] = playerDownAnimations;

	std::map<AnimationTypes, std::vector<AnimationFrame>> playerLeftAnimations;
	playerLeftAnimations[AnimationTerms::ATTACK] = std::vector<AnimationFrame>{
		std::make_pair(PACMAN, ATTACK_LEFT), std::make_pair(PACMAN, ALT),
		std::make_pair(PACMAN, ATTACK_LEFT), std::make_pair(PACMAN, LEFT)
	};
	animationsPlayer[CharacterOrientation::Left] = playerLeftAnimations;

	std::map<AnimationTypes, std::vector<AnimationFrame>> playerRightAnimations;
	playerRightAnimations[AnimationTerms::ATTACK] = std::vector<AnimationFrame>{
		std::make_pair(PACMAN, ATTACK_RIGHT), std::make_pair(PACMAN, ALT),
		std::make_pair(PACMAN, ATTACK_RIGHT), std::make_pair(PACMAN, RIGHT)
	};
	animationsPlayer[CharacterOrientation::Right] = playerRightAnimations;


}
