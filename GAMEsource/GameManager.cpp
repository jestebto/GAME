#include "pch.h"
#include "GameManager.h"
#include "UserInputType.h"

#include <thread> //sleep_for()
#include <chrono> //milliseconds
#include <string>
#include <iostream> //printing the debug console text when game over.
#include <exception>
#include <stdexcept>


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
		catch (std::exception) {
			outputManager->showGenericErrorScreen();
			this->programState = ProgramState::ERROR;
		}
		catch (std::string msg)
		{
			std::cout << msg << '\n';
			// Don't show the error screen, because the output manager itself might have failed
			this->programState = ProgramState::ERROR;
		}

		while (this->programState != ProgramState::CLOSING) {
			try {
				Update();
			}
			catch (std::exception &e) {
				std::cout << e.what();
				outputManager->showGenericErrorScreen();
				this->programState = ProgramState::ERROR;
			}
			catch (const char* msg)
			{
				std::cout << msg << '\n';
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
			//std::cout << "Sadly, it's game over...\n";
			outputManager->showGameOverScreen();
			break;
		case GameState::NOTLOADED:
			currentLevel = loadedStorageData->getNextLevel();
			DistributeData(currentLevel);
			break;
		default:
			throw std::runtime_error("A not expected state "); //TO DO: create custom exception?
			break;
		}
	}	
}

void GameManager::DistributeData(StorageLevelData* storageLevelData) {
	try {
		logicManager->createLevel(LogicData{ storageLevelData->logicData }, true);
	}
	catch (std::exception &e) {
		std::cout << "Exception at createLevel: "
			<< e.what();
		outputManager->showGenericErrorScreen();
		this->programState = ProgramState::ERROR;
	}
	try {
		if (programState != ProgramState::ERROR) {
			outputManager->loadLevel(OutputData{ storageLevelData->outputData });
		}
	}
	catch (std::exception &e) {
		std::cout << "Exception at loadLevel: "
			<< e.what();
		outputManager->showGenericErrorScreen();
		this->programState = ProgramState::ERROR;
	}
}

