#include "pch.h"
#include "HardCodedStorageManager.h"
#include <string>

static std::string defLevelLogic  = "0&0000-0110-0100-0000;1&001,1,0,3,;2&002,2,0,5,1,;";
static std::string defLevelOutput = "0&0000-0110-0100-0000;1&001,1,2,3,;2&002,2,0,5,1,;";
//"001/m&Default Map&0000-0110-0100-0000";


HardCodedStorageManager::HardCodedStorageManager()
	: defaultLevel(defLevelLogic, defLevelOutput) //this is a member initialization list, otherwise the member defaultLevel requires a default constructor (with no arguments)
{
	//std::string("001/m&Default Map&0000-0110-0100-0000/m&0000-0110-0100-0000;";
}


HardCodedStorageManager::~HardCodedStorageManager()
{
}


StorageData* HardCodedStorageManager::loadDefaultLevel() {
	StorageData* defaultLevelCopy = new StorageData(std::string(defLevelLogic), std::string(defLevelOutput)); //<TO DO JOSE> find out if this is actually a copy, create a test
	return defaultLevelCopy;
}

