#pragma once
#include "IStorageManager.h"
#include "StorageLevelData.h"
class HardCodedStorageManager : public IStorageManager
{
public:
	HardCodedStorageManager();
	~HardCodedStorageManager();
	StorageLevelData* loadDefaultLevel();
	StorageGameData* loadDefaultGame();

private:
	StorageLevelData defaultLevel;
	StorageGameData defaultGame;
};

