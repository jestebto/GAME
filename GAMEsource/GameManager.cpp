#include "pch.h"
#include "GameManager.h"
#include "UserInputType.h"

#include <SDL2/SDL.h> // Lior: this is for the timer functionality to limit frame rate and input rates
#include <thread> //sleep_for()
#include <chrono> //milliseconds
#include <string>
#include <iostream> //printing the debug console text when game over.

GameManager::GameManager()
{
	this->ExitGame = false;
	this->GameOver = false;
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
	//Initializes all 4 components making use of the ComponentFactory class
	storageManager = componentFactory.GetStorageManager();
	inputManager = componentFactory.GetInputManager();
	outputManager = componentFactory.GetOutputManager();
	logicManager = componentFactory.GetLogicManager();

	//Read the initial data (level) from the Storage component
	loadedStorageData = storageManager->loadDefaultGame();

	//state of the game is not GameOver anymore (if it was) because we just loaded a new level (will be useful for multilevel game)
	this->GameOver = false;
}

void GameManager::Update()
{
	//Updates sequentially the Input, Logic and Output components

	//Input
	UserInputType userInput = inputManager->getInput();

	if (userInput == UserInputType::Quit) {
		//<TO DO> send request to outputManager to show "Goodbye screen" (or ask for confirmation)
		this->ExitGame = true;
	}
	else if(GameOver == false){
		switch (logicManager->getGameState())
		{
		case GameState::UPANDRUNNING:
			logicManager->executeUserCommand(userInput);
			outputManager->update(logicManager->getLevelUpdates());
			//outputManager->update(userInput); // For testing
			break;
		case GameState::LEVELFINISHED:
			if (currentLevel->checkIsFinalLevel()) {
				this->GameOver = true;
				outputManager->showVictoryScreen();
			}
			else {
				currentLevel = loadedStorageData->getNextLevel();
				delete(this->outputManager);
				outputManager = componentFactory.GetOutputManager(); //TO DO: remove this line when outputManager->loadLevel properly clears out all previous data.
				DistributeData(currentLevel);
			}
			break;
		case GameState::VICTORY:
			outputManager->showVictoryScreen();
			break;
		case GameState::GAMEOVER:
			this->GameOver = true;
			std::cout << "Sadly, it's game over...\n";
			outputManager->showGameOverScreen();
			//std::this_thread::sleep_for(std::chrono::milliseconds(4000));
			break;
		case GameState::NOTLOADED:
			currentLevel = loadedStorageData->getNextLevel();
			DistributeData(currentLevel);
			break;
		default:
			throw "A not expected state ";
			break;
		}
	}	
}

void GameManager::DistributeData(StorageLevelData* storageLevelData) {
	logicManager->createLevel(LogicData{ storageLevelData->logicData });
	outputManager->loadLevel(OutputData{ storageLevelData->outputData });
}

int GameManager::Add(int x, int y) {
	//This is a dummy method to try the GAMEtest project
	//<TO DO JOSE> remove when we already have other tests
	return x - y;
}
