#include "TileManager.h"


TileManager::TileManager(SDL_Texture* texture)
{
	this->sheetSprites = texture;
}

TileManager::~TileManager()
{
	SDL_DestroyTexture(sheetSprites);
}

SDL_Texture* TileManager::getSheet() {
	return this->sheetSprites;
}