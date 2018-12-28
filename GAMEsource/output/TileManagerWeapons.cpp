#include "TileManagerWeapons.h"



TileManagerWeapons::TileManagerWeapons(SDL_Texture* texture) : TileManager(texture)
{
	// Pre-make the map for the tiles.
	// Note: this does not require the texture
	createTileMap();
	// Pre-make the animation frame for the tiles.
	//createAnimationSequences(); //no animation sequences defined
}


TileManagerWeapons::~TileManagerWeapons()
{
}

SDL_Rect* TileManagerWeapons::getTile(std::unique_ptr<GameSprite> const& element) {
	try {
		return &tileSet.at(element->getArt()).at(element->getDescription()); // &tileSet[art][des] does unwanted behaviour: creates a default element if it can't find the element}
	}
	catch (std::out_of_range)
	{
		//std::cout << "requested sprite is not defined in this tile manager" << '\n';
		return &tileSet[SpriteAttributes::ERROR][SpriteAttributes::DEFAULT];
	}
}

SDL_Rect* TileManagerWeapons::getTile(SpriteAttributes::ArtType art, SpriteAttributes::Description des) {
	try {
		return &tileSet.at(art).at(des); // &tileSet[art][des] does unwanted behaviour: creates a default element if it can't find the element
	}
	catch (std::out_of_range) {
		//std::cout << "requested sprite is not defined in this tile manager" << '\n';
		return &tileSet[SpriteAttributes::ERROR][SpriteAttributes::DEFAULT];
	}
}

std::vector<AnimationFrame>* TileManagerWeapons::getAnimationFrames(GameSprite* element, SpriteAttributes::ArtType type, SpriteAttributes::AnimationTypes action) {
	// return empty vector since no animation sequences have been defined
	std::vector<AnimationFrame>* emptyAnimationVector{};
	return emptyAnimationVector;
}

void TileManagerWeapons::createAnimationSequences() {
	// no animation sequences defined
};

/// From the Pacman Code
void TileManagerWeapons::createTileMap()
{
	using namespace SpriteAttributes;

	const int size = tileSize;
	const int o = 0; // offset in bitmap (both in x and y)

	std::map<Description, SDL_Rect> fireSword;
	fireSword[DEFAULT] = { o + size * 15, o + size * 1, size, size };
	tileSet[FIRE_SWORD] = fireSword;


	std::map<Description, SDL_Rect> potionRed;
	potionRed[DEFAULT] = { o + size * 5, o + size * 5, size, size };
	tileSet[APPLE] = potionRed;	// use an apple, since it is the same description used for the Pacman code
	// this shows that you can easily switch between the tile sets

	std::map<Description, SDL_Rect> error;
	error[DEFAULT] = { o + size * 14, o + size * 7, size, size };
	tileSet[ERROR] = error;

}