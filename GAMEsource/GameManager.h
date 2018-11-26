#pragma once
#include "ComponentFactory.h"
#include "IStorageManager.h"
#include "IInputManager.h"
#include "ILogicManager.h"
#include "IOutputManager.h"


class GameManager
{
public:
	GameManager();
	~GameManager();

	void StartGame();
	static int Add(int x, int y); //<TO DO JOSE> remove this. It's a dummy function to try the GAMEtest project

private:
	bool ExitGame;
	ComponentFactory componentFactory;
	IStorageManager* storageManager;
	IInputManager* inputManager;
	ILogicManager* logicManager;
	IOutputManager* outputManager;
	void SetupGame();
	void Update();
};

