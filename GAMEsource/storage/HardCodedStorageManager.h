#ifndef HARDCODEDSTORAGEMANAGER_H
#define HARDCODEDSTORAGEMANAGER_H

#include "IStorageManager.h"
#include "StorageLevelData.h"
#include "pch.h"
#include <string>

/**
* Contains hardcoded level data in the form of strings.
*
*/
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

#endif /* HARDCODEDSTORAGEMANAGER_H */