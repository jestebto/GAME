#pragma once
#include "ComponentFactory.h"
#include "IStorageManager.h"
#include "IInputManager.h"
#include "ILogicManager.h"
#include "IOutputManager.h"
#include "StorageLevelData.h"
#include "StorageGameData.h"
#include "ProgramState.h"


class GameManager
{
public:
	GameManager();
	~GameManager();

	void StartGame();
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

