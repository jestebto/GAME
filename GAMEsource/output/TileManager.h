/*
 *  Created on: 12 December, 2018
 *      Author: Lior Sinai
 * Description: manages Sprites for the Graphic Interface
 */


#ifndef TILE_MANAGER_H
#define TILE_MANAGER_H

#include "GameSprite.h"
#include "CharSprite.h"
#include "UserInputType.h" // for test purposes, else this class is not supposed to know about the UserInput
#include "AnimationFrame.h"

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <memory>

// For the animations:
#include <thread> //sleep_for()
#include <chrono> //milliseconds

/**
* Pure virtual class that manages Sprites for the GraphicOutputManager. It provides an abstract interface for the GraphicOutputManager.
* Different TileManagers can be instantiated for different tile set images/SDL_Textures.
* This seperates the complex task of creating and managing a tile set from the relatively simple task of printing sprites.
* Also contains animation functions (these will be moved to a new another class).
*/

class TileManager
{
public: /// Functions to be called by GraphicOutputManager
	TileManager(SDL_Texture*);
	~TileManager();

	/// pass the sheet so that it can be used in a renderer (in the GraphicOutputManager)
	SDL_Texture* getSheet();
	
	/// getTile for a unique Sprite
	virtual SDL_Rect* getTile(std::unique_ptr<GameSprite> const&) =0; 
	/// getTile for general printing e.g. for the background
	virtual SDL_Rect* getTile(SpriteAttributes::ArtType, SpriteAttributes::Description)=0;

	/// Get a vector of animation frames.
	virtual std::vector<AnimationFrame>* getAnimationFrames(GameSprite*, SpriteAttributes::ArtType,
		SpriteAttributes::AnimationTypes)=0;

protected:	
	/// Stores tiles to use wtih getTile
	/// tileSet[<ArtType>][<Description>]
	/// \see ArtType
	/// \see Description
	std::map<SpriteAttributes::ArtType, std::map<SpriteAttributes::Description, SDL_Rect>> tileSet;

private:
	/// Loaded SDL texture with all sprite bitmaps.
	SDL_Texture *sheetSprites;

	/// Seperate tiles into a tileSet map
	virtual void createTileMap() = 0; //Note: this was the old separateTiles(). New name to show that it doesn't actually seperate them; it only creates an index of where each sprite is in the bigger picture
	virtual void createAnimationSequences()=0; ///< create a list of connected sprites and descriptions to use in an animation sequence

};

#endif // TILE_MANAGER_H