#ifndef TILEMANAGERWEAPONS_H
#define TILEMANAGERWEAPONS_H

#include "TileManager.h"
class TileManagerWeapons :
	public TileManager
{
public:
	TileManagerWeapons(SDL_Texture*);
	~TileManagerWeapons();

	/// getTile for a unique Sprite
	SDL_Rect* getTile(std::unique_ptr<GameSprite> const&);
	/// getTile for general printing e.g. for the background
	SDL_Rect* getTile(SpriteAttributes::ArtType, SpriteAttributes::Description);

	/// Returns an empty vector, since no animations are defined for this tile set
	std::vector<AnimationFrame>* getAnimationFrames(GameSprite*, SpriteAttributes::ArtType, SpriteAttributes::AnimationTypes);

	/** 
	* tile size for each Sprite. 
	* This is NOT the same as the graphic output manager tile size
	* Therefore the renderer has to stretch the tile -> slows down rendering if there are too many sprites
	*/
	const int tileSize = 16; 

private:
	void createTileMap();
	void createAnimationSequences();
};

#endif /* TILEMANAGERWEAPONS_H */