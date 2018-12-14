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

#ifndef GRAPHIC_OUTPUT_MANAGER_H
#define GRAPHIC_OUTPUT_MANAGER_H

#include "IOutputManager.h"
#include "UserInputType.h" /// for test purposes, else this class is not supposed to know about the UserInput
#include "GameSprite.h"
#include "SpriteManager.h" /// all sprite related functions are in this class
#include "DataToolkit.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <vector>

class GraphicOutputManager: public IOutputManager
{
public:
	/// Constructor 
	/// Note: all initialisation is done in GraphicInterface::loadlevel()
	GraphicOutputManager();

	/// UI objects should not be copied or moved.
	GraphicOutputManager(const GraphicOutputManager&) = delete;
	GraphicOutputManager(const GraphicOutputManager&&) = delete;
	GraphicOutputManager &operator=(const GraphicOutputManager &) = delete;

	/// Destructor 
	/// Fully de-initializes the UI, including closing the main window.
	~GraphicOutputManager();

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
	
	//! Displays the Victory screen
	void showVictoryScreen();

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
	//void seperateTiles();

	/// Draws walls onto the screen according to \p map
	/// \param map A 2-by-2 grid indicating which grid locations are walls.
	void drawBackground(std::vector<std::vector<int>> &map);
	void drawLives();

	void drawBitmap(SDL_Texture*);


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
	//SDL_Texture *sheet; // moved to SpriteManager
	/// Loaded SDL texture with the game over screen
	SDL_Texture *gameOverScreen;
	/// Loaded SDL texture with the victory screen
	SDL_Texture *victoryScreen;

	/// 2d array containing the map, a 1 is a wall.
	std::vector<std::vector<int>> levelMap;
	int screenWidth;
	int screenHeight;

	//*spriteManager; //< makes a SpriteManager for this OutputManager
	std::unique_ptr<SpriteManager> spriteManager; //< makes a unique SpriteManager for this OutputManager
	
	/// Map of GameSprites in use
	/// The key is the ID
	std::map<std::string, std::unique_ptr<GameSprite>> spriteObjects;

	enum { TILESIZE = 24 };

	int lives = 3;//<store number of lives the character has

};

#endif /* GRAPHIC_OUTPUT_MANAGER_H*/

