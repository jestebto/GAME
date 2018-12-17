#pragma once

/*
 *  Created on: 12 December, 2018
 *      Author: Lior Sinai
 * Description: manages Sprites for the Graphic Interface
 */


#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "GameSprite.h"
#include "CharSprite.h"
#include "UserInputType.h" // for test purposes, else this class is not supposed to know about the UserInput
#include "Animation.h"

#include <SDL2/SDL.h>
#include <map>
#include <vector>

// For the animations:
#include <thread> //sleep_for()
#include <chrono> //milliseconds

class SpriteManager
{
public: /// Functions to be called by GraphicOutputManager
	SpriteManager();
	~SpriteManager();

	// TOD Lior: the SpriteManager should own this function
	/// create the texture sheet which has all the artworks for the sprites
	void setSheet(SDL_Texture*);
	
	/// pass the sheet so that it can be used in a renderer (in the GraphicOutputManager)
	SDL_Texture* getSheet();
	
	/// getTile for a unique Sprite
	SDL_Rect* getTile(std::unique_ptr<GameSprite> const&); 
	/// getTile for general printing e.g. for the background
	SDL_Rect* getTile(SpriteAttributes::ArtType, SpriteAttributes::Description); 

	/// Get a vector of animation frames. Search through different private map<>animations defined below
	std::vector<AnimationTerms::AnimationFrame>* getAnimationFrames(std::unique_ptr<GameSprite> const&, SpriteAttributes::ArtType, AnimationTerms::AnimationTypes);
	
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
	std::map <CharacterOrientation, std::map<AnimationTerms::AnimationTypes, std::vector<AnimationTerms::AnimationFrame>>> animationsPlayer;
	std::map <SpriteAttributes::ArtType, std::map<AnimationTerms::AnimationTypes, std::vector<AnimationTerms::AnimationFrame>>> animationsOther;

	enum { PACMAN_TILESIZE = 24 }; //< tile size for each Sprite. Does not have to be the same as the graphic interface size
};

#endif // SPRITE_MANAGER_H