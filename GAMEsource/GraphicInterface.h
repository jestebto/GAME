#pragma once

/*
 *  Created on: 28 November, 2018
 *      Author: Lior Sinai
 * Description: Graphic user interface using SDL2 library. 
 *              Based on the UI class in the Pacman code:
 *              Created on : Jan 29, 2015
 *				Author     : frits
 *				Group      : TA's
 */

#ifndef GRAPHIC_INTERFACE_H
#define GRAPHIC_INTERFACE_H

#include "IOutputManager.h"
#include "UserInputType.h" /// for test purposes, else this class is not supposed to know about the UserInput
#include "GameSprite.h"
#include "SpriteManager.h" /// all sprite related functions are in this class

#include <SDL2/SDL.h>

#include <map>
#include <vector>

class GraphicInterface: public IOutputManager
{
public:
	/// Constructor 
	/// Note: all initialisation is done in GraphicInterface::loadlevel()
	GraphicInterface();

	/// UI objects should not be copied or moved.
	GraphicInterface(const GraphicInterface&) = delete;
	GraphicInterface(const GraphicInterface&&) = delete;
	GraphicInterface &operator=(const GraphicInterface &) = delete;

	/// Destructor 
	/// Fully de-initializes the UI, including closing the main window.
	~GraphicInterface();

	/// Initialize the UI fully.
	/// Loads data
	/// Creates a main (SDL) window for rendering, and loads the sprites from a
	/// bitmap on disk.
	/// Public because called by Game Manager
	void loadLevel(OutputData);

	/// Update the screen
	/// - Draw the background
	/// - Draw the score
	/// - Draw the remaining lives
	/// - Draw the objects (last)
	void update(std::vector<std::shared_ptr<DataUpdate>> data);

	/// A test update that takes in user inputs directly, so that the logic component can be completely bypassed
	/// This is useful for testing animations
	void update(UserInputType);

	//! Displays the Game Over screen
	void showGameOverScreen();

private:
	///
	/// Initialise a window for SDL
	///
	void init();
	/// Read the map layout and add into the map array
	void setBackground(const std::string&);

    /// Loads the sprite sheet.
    void loadTextures();

	/// Seperate tiles into a tileSet map. Usage is:
	/// tileSet[<ArtType>][<Direction>]
	/// and the tile set itself is in GraphicInterface::sheet
	void seperateTiles();

	/// Draws walls onto the screen according to \p map
	/// \param map A 2-by-2 grid indicating which grid locations are walls.
	void drawBackground(std::vector<std::vector<int>> &map);
	void drawLives();

	/// Loads an image into a texture on the rendering device
	/// \param file The image file to load
	/// \return the loaded texture, or nullptr if something went wrong.
	SDL_Texture *loadTexture(const std::string &file);

	private:
	/// Main game UI window.
	SDL_Window *window;
	/// SDL Renderer to draw items onto #window.
	SDL_Renderer *renderer;
	/// Loaded SDL texture with all sprite bitmaps.
	SDL_Texture *sheet;
	/// Loaded SDL texture with the game over screen
	SDL_Texture *gameOverScreen;

	/// 2d array containing the map, a 1 is a wall.
	std::vector<std::vector<int>> levelMap;
	int screenWidth;
	int screenHeight;

	SpriteManager* spriteManager; //< keeps the 

	/// Map containing all the game objects.
	///
	/// Stores tiles to use in GraphicInterface::sheet. Usage is:
	/// tileSet[<type>][<direction>]
	/// \see ArtType
	/// \see Direction
	std::map<SpriteAttributes::ArtType, std::map<SpriteAttributes::Direction, SDL_Rect>> tileSet;

	/// Map of GameSprites in use
	/// The key is the ID
	std::map<std::string, GameSprite*> spriteObjects;

		enum { TILESIZE = 24 };

		int lives = 3;//<store number of lives the character has

};

#endif /* GRAPHIC_INTERFACE_H*/

