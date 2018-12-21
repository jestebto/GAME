#pragma once
#include "ComponentFactory.h"
#include "storage/IStorageManager.h"
#include "input/IInputManager.h"
#include "logic/ILogicManager.h"
#include "output/IOutputManager.h"
#include "storage/StorageLevelData.h"
#include "storage/StorageGameData.h"
#include "ProgramState.h"

/*
* The main class which controls runs during the programs execution. 
* It owns an IStorageManager, an IInputManager, an ILogicManager and an IOutputManager.
* It passes information between all 4 interfaces.
*/

class GameManager
{
public:
	GameManager();
	~GameManager();

	void StartGame(); //!< This is the one and only call that needs to be done to run the game from the main() function, and will last until the end of the program.
	static int Add(int x, int y); //<TO DO JOSE> remove this. It's a dummy function to try the GAMEtest project

private:
	StorageLevelData* currentLevel;
	//bool ExitGame;
	//bool GameOver;
	ProgramState programState;
	StorageGameData* loadedStorageData;
	ComponentFactory componentFactory;
	IStorageManager* storageManager;
	IInputManager* inputManager;
	ILogicManager* logicManager;
	IOutputManager* outputManager;
	void SetupGame();
	void DistributeData(StorageLevelData*);
	void Update();
};


