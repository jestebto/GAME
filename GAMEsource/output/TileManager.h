#pragma once

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

// For the animations:
#include <thread> //sleep_for()
#include <chrono> //milliseconds

/**
* Manages Sprites for the GraphicOutputManager. 
* It provides an abstract interface to separate printing sprites to the SDL_renderer
* from the complexity of creating a tile map for each tile set SDL_texture.
* Also contains animation functions (these will be moved to a new another class)
*/

class TileManager
{
public: /// Functions to be called by GraphicOutputManager
	TileManager(SDL_Texture*);
	~TileManager();

	/// pass the sheet so that it can be used in a renderer (in the GraphicOutputManager)
	SDL_Texture* getSheet();
	
	/// getTile for a unique Sprite
	SDL_Rect* getTile(std::unique_ptr<GameSprite> const&); 
	/// getTile for general printing e.g. for the background
	SDL_Rect* getTile(SpriteAttributes::ArtType, SpriteAttributes::Description); 

	/// Get a vector of animation frames. Search through different private map<>animations defined below
	std::vector<AnimationFrame>* getAnimationFrames(GameSprite*, SpriteAttributes::ArtType, SpriteAttributes::AnimationTypes);
	
private:
	/// Loaded SDL texture with all sprite bitmaps.
	SDL_Texture *sheetSprites;

	/// Seperate tiles into a tileSet map. Usage is:
	/// tileSet[<ArtType>][<Direction>]
	/// and the tile set itself is in GraphicInterface::sheet
	void createTileMap(); //Note: this was the old separateTiles(). New name to show that it doesn't actually seperate them; it only creates an index of where each sprite is in the bigger picture
	void createAnimationSequences();

	/// Stores tiles to use in GraphicInterface::sheet. Usage is:
	/// tileSet[<type>][<direction>]
	/// \see ArtType
	/// \see Direction
	std::map<SpriteAttributes::ArtType, std::map<SpriteAttributes::Description, SDL_Rect>> tileSet;

	/// Hard code the animation sequences
	/// For the player, use a map with the key as the orientation and the action
	/// For the other objects, the orientation is not important, so use the key as object type and the action
	/// An art type and a description uniquely defines an animation frame
	std::map <CharacterOrientation, std::map<SpriteAttributes::AnimationTypes, std::vector<AnimationFrame>>> animationsPlayer;
	std::map <SpriteAttributes::ArtType, std::map<SpriteAttributes::AnimationTypes, std::vector<AnimationFrame>>> animationsOther;

	enum { PACMAN_TILESIZE = 24 }; //< tile size for each Sprite. Does not have to be the same as the graphic interface size
};

#endif // TILE_MANAGER_H