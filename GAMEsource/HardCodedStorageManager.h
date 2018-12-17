#pragma once
#include "IStorageManager.h"
#include "StorageLevelData.h"
class HardCodedStorageManager : public IStorageManager
{
public:
	HardCodedStorageManager(); 
	~HardCodedStorageManager();  
	StorageLevelData* loadDefaultLevel(); //!< load a single hardcoded level
	StorageGameData* loadDefaultGame(); //!< load a hardcorded game with multiple levels

private:
	StorageLevelData defaultLevel;
	StorageGameData defaultGame;
};

