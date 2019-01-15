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
#include "UserInputType.h" // for test purposes, else this class is not supposed to know about the UserInput
#include "GameSprite.h"
#include "TileManagerPacman.h" // all sprite related functions are in this class
#include "TileManagerWeapons.h"
#include "DataToolkit.h"
#include "AnimationFrame.h"
#include "AnimationRequest.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <map>
#include <vector>

/// An output manager that manages a Window and a Graphic User Interface
/// This class owns GameSprite objects, SpriteManager(s), SDL textures and a SDL window and renderer.
/// It is dependent on SpriteManager to execute many of the tasks related to dynamic sprites.
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

	/// Play an animation for a given GameSprite and Animation
	void playAnimation(AnimationRequest);
	/// Play multiple animations at once
	void playAnimationMany(std::vector<AnimationRequest>);

	//! Displays the Game Over screen
	void showGameOverScreen();
	
	//! Displays the Victory screen
	void showVictoryScreen();

	//! Displays the generic error screen (when the error is unknown)
	void showGenericErrorScreen();

private:
	///
	/// Initialise a window for SDL
	///
	void init();
	/// Read the map layout and add into the map array
	void setBackground(const std::string&);

	/// Seperate tiles into a tileSet map. Usage is:
	/// tileSet[<ArtType>][<Direction>]
	/// and the tile set itself is in GraphicInterface::sheet
	//void seperateTiles();

	// drawing functions
	void drawBackground(std::vector<std::vector<int>> &map); ///< Draws walls onto the screen according to \p map
	void drawLives(); ///< draw Pacman sprites at the bottom to indicate the number of lives
	void drawAnimationFrame(AnimationFrame, GameSprite*); ///< draw a single animation frame for a spirte
	void drawBitmap(SDL_Texture*); ///< draw an image over the entire screen


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
	/// Loaded SDL texture with the generic error screen
	SDL_Texture *genericErrorScreen;

	/**
	* Declare constants used to keep the screen and tile size fixed
	* Also declare enums to specify the tile manager to use for each game sprites
	* TM0 -> use spriteManager
	* TM1 -> use weaponManager (but not for animations!!)
	*/
	enum { TILESIZE = 24, SCREEN_WIDTH = 22, SCREEN_HEIGHT = 21, TM0,TM1 }; // note: title bar is an effective +1 to the screen height

	/// 2d array containing the map, a 1 is a wall.
	std::vector<std::vector<int>> levelMap;
	int xOffset=0; //< offset to centre the map in the display
	int yOffset=0; //< offset to centre the map in the display

	std::unique_ptr<TileManager> spriteManager; ///< makes a unique TileManager for the sprites for this OutputManager
	std::unique_ptr<TileManager> weaponManager; ///< makes a unique TileManager for the weapons for this OutputManager

	/// Map of GameSprites in use
	/// The key is the ID
	std::map<std::string, std::unique_ptr<GameSprite>> spriteObjects;

	int lives;//<store number of lives the character has
	bool hasWeapon = false;
};

#endif /* GRAPHIC_OUTPUT_MANAGER_H */

