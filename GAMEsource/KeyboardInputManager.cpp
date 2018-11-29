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

	// Lior TODO add this??
	// Start timer for game update, call this function every 100 ms.
	//SDL_TimerID timer_id =
		//SDL_AddTimer(100, gameUpdate, static_cast<void *>(nullptr));

	// set timeout to limit frame rate
	//Uint32 timeout = SDL_GetTicks() + 20; //commented out by Jose

	// Handle the input
	// Can be moved to InputManager later
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		// Quit button.
		/*
		if (e.type == SDL_QUIT) {
			ExitGame = true;
		}
		*/ //commented out by Jose
		//<TO DO JOSE> consider a proper way of checking for the window closed event from GUI and detecting it from GameManager (probably a boolean in the IOuputManager)

		// All keydown events
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				std::cout << "Pressed LEFT!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Left;
			case SDLK_RIGHT:
				std::cout << "Pressed RIGHT!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Right;
			case SDLK_UP:
				std::cout << "Pressed UP!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Up;
			case SDLK_DOWN:
				std::cout << "Pressed DOWN!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Down;
			case SDLK_ESCAPE:
				std::cout << "Pressed ESC!\n"; //<TO DO JOSE> comment out or remove (DEBUG)
				return UserInputType::Right; //Hey, if you came here because you pressed Esc and wondered why it moved to the right: it's temporary, I will change it, I want to have something that works first. You thought this comment was large enough? Tralala lala lala
			}
		}
	}
	// Lior TODO add this??
	//SDL_RemoveTimer(timer_id);

}
