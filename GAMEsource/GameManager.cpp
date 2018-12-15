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
	this->programState = ProgramState::CREATED;
	this->componentFactory = ComponentFactory{};
}

GameManager::~GameManager()
{
}

void GameManager::StartGame()
{
	if (this->programState == ProgramState::CREATED) {
		try {
			SetupGame();
			this->programState = ProgramState::RUNNING;
		}
		catch (std::exception& e) {
			outputManager->showGenericErrorScreen();
			this->programState = ProgramState::ERROR;
		}

		while (this->programState != ProgramState::CLOSING) {
			try {
				Update();
			}
			catch (std::exception e) {
				outputManager->showGenericErrorScreen();
				this->programState = ProgramState::ERROR;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
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
}

void GameManager::Update()
{
	//Updates sequentially the Input, Logic and Output components

	//Input
	UserInputType userInput = inputManager->getInput();

	if (userInput == UserInputType::Quit) {
		//<TO DO> send request to outputManager to show "Goodbye screen" (or ask for confirmation)
		this->programState = ProgramState::CLOSING;
	}
	else if(this->programState == ProgramState::RUNNING){
		switch (logicManager->getGameState())
		{
		case GameState::UPANDRUNNING:
			logicManager->executeUserCommand(userInput);
			outputManager->update(logicManager->getLevelUpdates());
			//outputManager->update(userInput); // For testing
			break;
		case GameState::LEVELFINISHED:
			if (currentLevel->checkIsFinalLevel()) {
				this->programState = ProgramState::ENDOFTHEGAME;
				outputManager->showVictoryScreen();
			}
			else {
				currentLevel = loadedStorageData->getNextLevel();
				DistributeData(currentLevel);
			}
			break;
		case GameState::VICTORY:
			this->programState = ProgramState::ENDOFTHEGAME;
			outputManager->showVictoryScreen();
			break;
		case GameState::GAMEOVER:
			this->programState = ProgramState::ENDOFTHEGAME;
			std::cout << "Sadly, it's game over...\n";
			outputManager->showGameOverScreen();
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
	logicManager->createLevel(LogicData{ storageLevelData->logicData}, true);
	outputManager->loadLevel(OutputData{ storageLevelData->outputData });
}

int GameManager::Add(int x, int y) {
	//This is a dummy method to try the GAMEtest project
	//<TO DO JOSE> remove when we already have other tests
	return x - y;
}
