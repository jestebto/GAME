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
#include "UserInputType.h" /// for test purposes, else this class is not supposed to know about the UserInput

#include <SDL2/SDL.h>
#include <map>
#include <vector>

// For the animations:
#include <thread> //sleep_for()
#include <chrono> //milliseconds

class SpriteManager
{
public: /// All public since needs to be accessed by GraphicInterface
	typedef std::pair<SpriteAttributes::ArtType, SpriteAttributes::Description> AnimationFrame;

	SpriteManager();
	~SpriteManager();

	/// create the texture sheet which has all the artworks for the sprites

	/// Option to give SpriteManager ownership of its own sheet. 
	void setSheet(SDL_Texture*);
	SDL_Texture* getSheet();
	
	/// get a tile on SpriteManager::sheet 
	SDL_Rect* getTile(std::unique_ptr<GameSprite> const&); //< getTile for a unique object in the game
	SDL_Rect* getTile(SpriteAttributes::ArtType, SpriteAttributes::Description); //< getTile for generic printing e.g. for the background

	/// Get a vector of animation frames
	/// Search through the different map<>animations defined below
	//std::vector<AnimationFrame>* getAnimationFrames(std::unique_ptr<GameSprite> const&, DataUpdate::ObjectType, DataUpdate::Action);
	
private:
	/// Loaded SDL texture with all sprite bitmaps.
	//Ownership of this sheet is currently with GraphicInterface
	SDL_Texture *sheetSprites;

	/// Seperate tiles into a tileSet map. Usage is:
	/// tileSet[<ArtType>][<Direction>]
	/// and the tile set itself is in GraphicInterface::sheet
	void createTileMap(); //Note: this was the old separateTiles(). New name to show that it doesn't actually seperate them; it only creates an index of where each sprite is in the bigger picture
	void createAnimations();

	/// Stores tiles to use in GraphicInterface::sheet. Usage is:
	/// tileSet[<type>][<direction>]
	/// \see ArtType
	/// \see Direction
	std::map<SpriteAttributes::ArtType, std::map<SpriteAttributes::Description, SDL_Rect>> tileSet;

	/// Hard code the animation sequences
	/// For the player, use a map with the key as the orientation and the action
	/// For the other objects, the orientation is not important, so use the key as object type and the action
	/// An art type and a description uniquely defines an animation frame
	std::map <CharacterOrientation, std::map<DataUpdate::Action, std::vector<AnimationFrame>>> animationsPlayer;
	std::map <DataUpdate::ObjectType, std::map<DataUpdate::Action, std::vector<AnimationFrame>>> animationsOther;

	/// Use a private helper function to determine which map to use
	///Animation getAnimation(DataUpdate::ObjectType, DataUpdate::Action, CharacterOrientation);
	
	enum { PACMAN_TILESIZE = 24 }; //< tile size for each Sprite. Does not have to be the same as the graphic interface size
};

#endif // SPRITE_MANAGER_H