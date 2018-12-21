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
	if (currentLevel > levels.size()) throw std::exception("Error: tried to access more levels than available."); //TO DO: is this the right type of exception?
	//StorageLevelData l = levels[currentLevel - 1];
	return &(this->levels[currentLevel - 1]);
}

void StorageGameData::add(StorageLevelData* level) {
	this->levels.push_back(*level);
}
