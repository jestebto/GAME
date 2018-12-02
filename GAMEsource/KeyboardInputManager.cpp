#include "pch.h"
#include "KeyboardInputManager.h"
#include <SDL2/SDL.h>
#include "UserInputType.h"
#include <iostream>



KeyboardInputManager::KeyboardInputManager()
{
}


KeyboardInputManager::~KeyboardInputManager()
{
}

UserInputType KeyboardInputManager::getInput()
{

	// Based on the SDL2 toolkit.
	// See https://wiki.libsdl.org/FrontPage
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		
		// Quit button.
		if (e.type == SDL_QUIT) {
			std::cout << "Pressed Quit!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
			return UserInputType::Quit;
		}

		// All events trigged by pushing a keyboard key down
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_a:
			case SDLK_LEFT:
				std::cout << "Pressed LEFT!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Left;
			case SDLK_d:
			case SDLK_RIGHT:
				std::cout << "Pressed RIGHT!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Right;
			case SDLK_w:
			case SDLK_UP:
				std::cout << "Pressed UP!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Up;
			case SDLK_s:
			case SDLK_DOWN:
				std::cout << "Pressed DOWN!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Down;
			case SDLK_ESCAPE:
				std::cout << "Pressed ESC!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Quit; 
			}
		}
	}
	return UserInputType::Nothing;
}
