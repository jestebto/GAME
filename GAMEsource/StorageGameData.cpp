#include "StorageGameData.h"

StorageGameData::StorageGameData()
{
	this->currentLevel = 0;
}


StorageGameData::~StorageGameData()
{
}

StorageLevelData* StorageGameData::getNextLevel() {
	this->currentLevel++;
	if (currentLevel > levels.size()) throw "Error: tried to access more levels than available.";
	//StorageLevelData l = levels[currentLevel - 1];
	return &(this->levels[currentLevel - 1]);
}

void StorageGameData::add(StorageLevelData* level) {
	this->levels.push_back(*level);
}
