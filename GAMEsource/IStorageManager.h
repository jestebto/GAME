#pragma once
#include "StorageLevelData.h"
#include "StorageGameData.h"

class IStorageManager
{
	/**
	* Interface to be implemented by a class acting as the manager of the Storage Component
	*/
public:
	virtual ~IStorageManager() = 0; //!< virtual destructor to be implemented in the class implementing the interface
	virtual StorageLevelData* loadDefaultLevel() = 0; //!< load a single level
	virtual StorageGameData* loadDefaultGame() = 0; //!< load multiple levels to form a single game
};