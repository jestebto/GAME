#include "pch.h"
#include "GameManager.h"
#include <string>

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
	//Initializes all 4 components making use of the ComponentFactory class
	storageManager = componentFactory.GetStorageManager();
	inputManager = componentFactory.GetInputManager();
	logicManager = componentFactory.GetLogicManager();
	outputManager = componentFactory.GetOutputManager();

	//Read the initial data (level) from the Storage component
	loadedStorageData = storageManager->loadDefaultLevel();

}

void GameManager::Update()
{
	//Updates sequentially the Input, Logic and Output components,
	//Input
	UserInputType input = inputManager->getInput();

	//Logic
	logicManager->executeUserCommand(input);

	//Output
		//<TO DO JOSE> implement when Class Level is ready to send updates
}

void GameManager::DistributeData() {
	std::string logicString;
	std::string outputString;

	//<TO DO JOSE> real implementation (this is mocking)
		/*
		This is an example (feel free to change it):
			001, map, content=
								0000
								0110
								0100
								0000
			002, player p, initial x=2, initial y=2, lives=3
		*/
	logicString = std::string("001/m&0000-0110-0100-0000;002/p&2&2&3");

	logicManager->createLevel(*(new LogicData(logicString)));
}

int GameManager::Add(int x, int y) {
	//This is a dummy method to try the GAMEtest project
	//<TO DO JOSE> remove when we already have other tests
	return x - y;
}
