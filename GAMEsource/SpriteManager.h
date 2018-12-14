#pragma once

/*
 *  Created on: 12 December, 2018
 *      Author: Lior Sinai
 * Description: manages Sprites for the Graphic Interface
 */


#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "GameSprite.h"
#include "UserInputType.h" /// for test purposes, else this class is not supposed to know about the UserInput

#include <SDL2/SDL.h>
#include <map>

class SpriteManager
{
public: /// All public since needs to be accessed by GraphicInterface
	SpriteManager();
	~SpriteManager();

	/// create the texture sheet which has all the artworks for the sprites

	/// Option to give SpriteManager ownership of its own sheet. 
	void setSheet(SDL_Texture*);
	SDL_Texture* getSheet();
	

	/// get a tile on SpriteManager::sheet 
	SDL_Rect* getTile(std::unique_ptr<GameSprite> const&); //< getTile for a unique object in the game
	SDL_Rect* getTile(SpriteAttributes::ArtType, SpriteAttributes::Direction); //< getTile for generic printing e.g. for the background
	
	/// Move a sprite to a position 
	/// Data is given by the logic manager
	void moveSprite(std::unique_ptr<GameSprite> const&, int, int);
	void moveSprite(std::unique_ptr<GameSprite> const&, int, int, SpriteAttributes::Direction);

	/// Move a sprite on the screen using user input.
	/// For test purposes only, as this is not connected to the logic
	void moveSprite(std::unique_ptr<GameSprite> const&, UserInputType);
	


private:
	/// Loaded SDL texture with all sprite bitmaps.
	//Ownership of this sheet is currently with GraphicInterface
	SDL_Texture *sheetSprites;


	/// Seperate tiles into a tileSet map. Usage is:
	/// tileSet[<ArtType>][<Direction>]
	/// and the tile set itself is in GraphicInterface::sheet
	void createTileMap(); //Note: this was the old separateTiles(). New name to show that it doesn't actually seperate them; it only creates an index of where each sprite is in the bigger picture

	/// Stores tiles to use in GraphicInterface::sheet. Usage is:
	/// tileSet[<type>][<direction>]
	/// \see ArtType
	/// \see Direction
	std::map<SpriteAttributes::ArtType, std::map<SpriteAttributes::Direction, SDL_Rect>> tileSet;

	enum { PACMAN_TILESIZE = 24 }; //< tile size for each Sprite. Does not have to be the same as the graphic interface size
};

#endif // SPRITE_MANAGER_H