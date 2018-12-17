#pragma once
#include <vector>
#include "StorageLevelData.h"

/// Store data for multiple levels
class StorageGameData
{
private:
	/// Keep track of the 
	unsigned currentLevel;
	std::vector<StorageLevelData> levels;

public:
	StorageGameData();
	~StorageGameData();
	StorageLevelData* getNextLevel();
	void add(StorageLevelData*);
	//void add(StorageLevelData, unsigned);
};

