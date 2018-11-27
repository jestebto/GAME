#include "pch.h"
#include "HardCodedStorageManager.h"
#include <string>

static std::string defLevel ="001/m&Default Map&0000-0110-0100-0000/m&0000-0110-0100-0000;";

HardCodedStorageManager::HardCodedStorageManager()
	: defaultLevel(defLevel) //this is a member initialization list, otherwise the member defaultLevel requires a default constructor (with no arguments)
{
	//std::string("001/m&Default Map&0000-0110-0100-0000/m&0000-0110-0100-0000;";
}


HardCodedStorageManager::~HardCodedStorageManager()
{
}


StorageData HardCodedStorageManager::loadDefaultLevel() {
	return this->defaultLevel;
}

