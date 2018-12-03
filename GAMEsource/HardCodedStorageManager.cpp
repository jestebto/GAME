#include "pch.h"
#include "HardCodedStorageManager.h"
#include <string>

//Logic: "logicItemType&field1,subfield21-subfield22,field3,......,;"
//Output: "outputItemType&field1,subfield21-subfield22,field3,......,;"

//Small level
//static std::string defLevelLogic = "0&0000-0110-0100-0000;1&001,1,0,3,;2&002,2,0,5,1,;";
//static std::string defLevelOutput = "0&0000-0110-0100-0000;1&001,1,2,3,;2&002,2,0,5,1,;";

//Test1
static std::string defLevelLogic = "0&000000000-011111110-010000110-010000010-010000010-010100010-011111110-000000000;1&001,3,2,3,;2&002,5,5,5,1,;2&003,6,3,5,1,;";
static std::string defLevelOutput = "0&000000000-011111110-010000110-010000010-010000010-010100010-011111110-000000000;1&001,3,2,3,;2&002,5,5,5,1,;2&003,6,3,5,1,;";

//Test2
//static std::string defLevelLogic = "0&00000000-01000000-00100000-00000001;1&001,0,0,3,;2&002,2,0,5,1,;";
//static std::string defLevelOutput = "0&00000000-01000000-00100000-00000001;1&001,0,0,3,;2&002,2,0,5,1,;";


//Cool level
//static std::string defLevelLogic = "0&01111111111111111111-01000000000000000001-01011111000000011111-01000001111111100010-01111100000000000010-01000110000000000010-01000000000000000010-01000110000000000010-01111111111111111110-00000000000000000000;1&001,0,0,3,;2&002,2,0,5,1,;";
//static std::string defLevelOutput = "0&01111111111111111111-01000000000000000000-01011111000000011111-01000001111111100010-01111100000000000010-01000110000000000010-01000000000000000010-01000110000000000010-01111111111111111110-00000000000000000000;1&001,0,0,3,;2&002,2,0,5,1,;";



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

