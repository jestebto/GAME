#include "pch.h"
#include "GameManager.h"
#include <SDL2/SDL.h> // Lior: this is for the timer functionality to limit frame rate and input rates
#include <thread> //sleep_for()
#include <chrono>


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
		
		Update();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	
}

void GameManager::SetupGame()
{
	//Setup all components
	storageManager = componentFactory.GetStorageManager();
	inputManager = componentFactory.GetInputManager();
	//logicManager = componentFactory.GetLogicManager();
	outputManager = componentFactory.GetOutputManager();

	//Read the initial data from the Storage component
		//<TO DO JOSE> implement
}

void GameManager::Update()
{
	//Updates sequentially the Input, Logic and Output components,
	//Input
	UserInputType userInput = inputManager->getInput();
	//Logic
		//<TO DO JOSE> implement
	//Output
		//<TO DO JOSE> implement
	outputManager->updateTest(userInput);
}

int GameManager::Add(int x, int y) {
	//This is a dummy method to try the GAMEtest project
	//<TO DO JOSE> remove when we already have other tests
	return x - y;
}
