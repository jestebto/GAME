#include "pch.h"
#include "GameManager.h"

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
	}
}

void GameManager::SetupGame()
{
	//Setup all components
	storageManager = componentFactory.GetStorageManager();
	inputManager = componentFactory.GetInputManager();
	logicManager = componentFactory.GetLogicManager();
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
}

int GameManager::Add(int x, int y) {
	//This is a dummy method to try the GAMEtest project
	//<TO DO JOSE> remove when we already have other tests
	return x - y;
}
