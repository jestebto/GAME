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
#include "UserInputType.h"
#include "GameSprite.h"

#include <SDL2/SDL.h>

#include <map>
#include <vector>

class GraphicInterface: public IOutputManager
{
public:
	/// Constructor initializes the UI fully.
	///
	/// Creates a main (SDL) window for rendering, and loads the sprites from a
	/// bitmap on disk.
	///
	/// \param map the map of the board
	GraphicInterface();
	// TODO: GraphicInterface(std::vector<std::vector<int>> map); // pass the map at the start


	// UI objects should not be copied or moved.
	GraphicInterface(const GraphicInterface&) = delete;
	GraphicInterface(const GraphicInterface&&) = delete;
	GraphicInterface &operator=(const GraphicInterface &) = delete;

	/// Destructor fully de-initializes the UI, including closing the main window.
	~GraphicInterface();


	void loadLevel(OutputData);

	/// Update the screen TODO
	/// - Draw the background
	/// - Draw the score
	/// - Draw the remaining lives
	/// - Draw the objects (last)
	///
	/// \param objects Objects that are drawn last.
	void update();

	/// A test update that takes in user inputs directly, so that the logic component can be completely bypassed
	/// This is useful for testing animations
	void updateTest(UserInputType);

	

	/// Move a sprite on the screen
	void moveSprite(UserInputType, std::string);

public:
	// list of GameSprites in use
	// TODO Lior: get this from the GameManager
	std::vector<GameSprite*> spriteObjects;

private:
	void init();

    /// Loads the sprite sheet.
    void loadTextures();

	/// Load the maps that contains all the clipping masks.
	///
	/// The clipping masks are stored in #clips. Usage is:
	/// `clips[<type>][<direction>]`.
	void loadMaps();

	/// Draws walls onto the screen according to \p map
	/// \param map A 2-by-2 grid indicating which grid locations are walls.
	void drawBackground(std::vector<std::vector<int>> &map);

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

	/// 2d array containing the map, a 1 is a wall.
	std::vector<std::vector<int>> map;

	/// Map containing all the game objects.
	///
	/// Stores the clipping masks related to UI::sheet. Usage is:
	/// `clips[<type>][<direction>]`.
	/// \see Type
	/// \see Direction
	std::map<ArtType, std::map<Direction, SDL_Rect>> clips;

	enum { TILESIZE = 24 };
};

#endif /* GRAPHIC_INTERFACE_H*/

