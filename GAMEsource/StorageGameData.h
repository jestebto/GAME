#pragma once
#include <vector>
#include "StorageLevelData.h"

class StorageGameData
{
private:
	unsigned currentLevel;
	std::vector<StorageLevelData> levels;

public:
	StorageGameData();
	~StorageGameData();
	StorageLevelData* getNextLevel();
	void add(StorageLevelData*);
	//void add(StorageLevelData, unsigned);
};

