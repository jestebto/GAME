#include "pch.h"
#include "GameManager.h"
#include <SDL2/SDL.h> // Lior: this is for the timer functionality to limit frame rate and input rates

GameManager::GameManager()
{
	this->componentFactory = ComponentFactory{};
}

GameManager::~GameManager()
{
}

void GameManager::StartGame()
{
	ExitGame = false;

	SetupGame();

	while (ExitGame == false) {
		// set timeout to limit frame rate
		Uint32 timeout = SDL_GetTicks() + 20;

		// Handle the input
		// Can be moved to InputManager later
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			// Quit button.
			if (e.type == SDL_QUIT) {
				ExitGame = true;
			}

			// All keydown events
			if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
				case SDLK_LEFT: // YOUR CODE HERE
					break;
				case SDLK_RIGHT: // YOUR CODE HERE
					break;
				case SDLK_UP: // YOUR CODE HERE
					break;
				case SDLK_DOWN: // YOUR CODE HERE
					break;
				case SDLK_ESCAPE:
					ExitGame = true;
					break;
				}
			}
		}
		Update();
	}
}

void GameManager::SetupGame()
{
	//Setup all components
	//storageManager = componentFactory.GetStorageManager();
	//inputManager = componentFactory.GetInputManager();
	//logicManager = componentFactory.GetLogicManager();
	outputManager = componentFactory.GetOutputManager();

	//Read the initial data from the Storage component
		//<TO DO JOSE> implement
}

void GameManager::Update()
{
	//Updates sequentially the Input, Logic and Output components,
	//Input
		//<TO DO JOSE> implement
	//Logic
		//<TO DO JOSE> implement
	//Output
		//<TO DO JOSE> implement
	outputManager->update();
}

int GameManager::Add(int x, int y) {
	//This is a dummy method to try the GAMEtest project
	//<TO DO JOSE> remove when we already have other tests
	return x - y;
}
