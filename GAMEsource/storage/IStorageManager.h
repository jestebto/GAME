#ifndef ISTORAGEMANAGER_H
#define ISTORAGEMANAGER_H

#include "StorageLevelData.h"
#include "StorageGameData.h"

/// Interface to be implemented by a class acting as the manager of the Storage Component
class IStorageManager
{
public:
	virtual ~IStorageManager() = 0; //!< virtual destructor to be implemented in the class implementing the interface
	virtual StorageLevelData* loadDefaultLevel() = 0; //!< load a single level
	virtual StorageGameData* loadDefaultGame() = 0; //!< load multiple levels to form a single game
};

#endif /* ISTORAGEMANAGER_H */