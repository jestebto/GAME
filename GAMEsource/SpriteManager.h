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
	SpriteManager(int);
	~SpriteManager();

	/// create the texture sheet which has all the artworks for the sprites
	/*
	void setSheet(SDL_Texture*);
	SDL_Texture* getSheet();
	*/

	/// Move a sprite to a position 
	/// Data is given by the logic manager
	void moveSprite(GameSprite*, int, int);

	/// Move a sprite on the screen using user input.
	/// For test purposes only, as this is not connected to the logic
	void moveSprite(GameSprite*, UserInputType);

	/// get the Tile when called
	/*
	void getTile(GameSprite*);
	*/

	/// Loaded SDL texture with all sprite bitmaps.
	//SDL_Texture *sheet;
private:


	/// Stores tiles to use in GraphicInterface::sheet. Usage is:
	/// tileSet[<type>][<direction>]
	/// \see ArtType
	/// \see Direction
	//	std::map<SpriteAttributes::ArtType, std::map<SpriteAttributes::Direction, SDL_Rect>> tileSetPacman;

	int size; //< tile size for each Sprite. Should be the same as the Graphic Interface tile size

};

#endif // SPRITE_MANAGER_H