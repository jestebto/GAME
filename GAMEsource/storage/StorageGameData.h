#ifndef STORAGEGAMEDATA_H
#define STORAGEGAMEDATA_H

#include <vector>
#include "StorageLevelData.h"
#include <exception>
#include <stdexcept>

/// Store data for multiple levels
class StorageGameData
{
private:
	/// Keep track of the 
	unsigned currentLevel; //!< Value used to keep track internally of how many levels have been extracted from this object already
	std::vector<StorageLevelData> levels; //!< std::vector containing each of the levels of the game that this object represents

public:
	StorageGameData();
	~StorageGameData();
	StorageLevelData* getNextLevel(); //!< Provides a pointer to the next level storage data
	void add(StorageLevelData*); //!< Adds the storage data of a level to the levels of this object
	//void add(StorageLevelData, unsigned);
};

#endif /* STORAGEGAMEDATA_H */
