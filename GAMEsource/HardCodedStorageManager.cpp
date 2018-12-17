#include "pch.h"
#include "HardCodedStorageManager.h"
#include <string>

//Logic: "logicItemType&field1,subfield21-subfield22,field3,......,;"
//Output: "outputItemType&field1,subfield21-subfield22,field3,......,;"

//Small level
//static std::string defLevelLogic = "0&0000-0110-0100-0000;1&001,1,0,3,;2&002,2,0,5,1,;";
//static std::string defLevelOutput = "0&0000-0110-0100-0000;1&001,1,2,3,;2&002,2,0,5,1,;";

//Test1
//static std::string defLevelLogic = "0&000000000-011111110-010000110-010000010-010000010-010100010-011111110-000000000;1&001,3,2,3,;2&002,5,5,5,1,;2&003,6,3,5,1,;";
//static std::string defLevelOutput = "0&000000000-011111110-010000110-010000010-010000010-010100010-011111110-000000000;1&001,3,2,3,;2&002,5,5,5,1,;2&003,6,3,5,1,;";

//Test2
//static std::string defLevelLogic = "0&00000000-01000000-00100000-00000001;1&001,0,0,3,;2&002,2,0,5,1,;";
//static std::string defLevelOutput = "0&00000000-01000000-00100000-00000001;1&001,0,0,3,;2&002,2,0,5,1,;";


//Cool level
static std::string defLevelLogic1 = "0&00000000000000000000-01111111111111111111-01000000000000002000-01011111000000011111-01000001111111100010-01111100000000000010-01000111111000000010-01000000000000001010-01000110000000000010-01111111111111111110-00000000000000000000;1&001,3,7,3,1,1,;2&002,11,6,1,1,;2&003,13,6,1,1,;2&004,9,2,1,1,;2&005,12,3,1,1,;2&006,19,2,1,1,;3&007,7,8,1,1,1,;";
static std::string defLevelOutput1 = "0&00000000000000000000-01111111111111111111-01000000000000002000-01011111000000011111-01000001111111100010-01111100000000000010-01000111111000000010-01000000000000001010-01000110000000000010-01111111111111111110-00000000000000000000;1&001,3,7,3,2,2,;2&002,11,6,1,1,;2&003,13,6,1,1,;2&004,9,2,1,1,;2&005,12,3,1,1,;2&006,19,2,1,1,;3&007,7,8,1,2,2,;";

//Multiple levels
static std::string defLevelLogic2 = "0&11111111111111111111-10001100000000010001-10000001011111010101-10001111000000012101-11111111011110111101-10000000000000000001-11111111111111111111;1&001,2,2,3,1,1,;2&002,8,5,1,1,;2&003,12,5,1,1,;2&004,8,2,1,1,;2&005,13,3,1,1,;2&006,18,2,1,1,;3&007,1,5,1,1,1,;";
static std::string defLevelOutput2 = "0&11111111111111111111-10001100000000010001-10000001011111010101-10001111000000012101-11111111011110111101-10000000000000000001-11111111111111111111;1&001,2,2,3,;2&002,8,5,1,1,;2&003,12,5,1,1,;2&004,8,2,1,1,;2&005,13,3,1,1,;2&006,18,2,1,1,;3&007,1,5,1,2,2,;";

static std::string defLevelLogic3 = "0&1111111111111111111-1000101000000000201-1000101101111111111-1000101000110000011-1101101000110000011-1100001000110000011-1110101101111101111-1100101000000000111-10001010000001111111-1001101111000000011-1011000001111111011-1011111101000000001-1000000101000011111-1011111101111011111-1010000000000000001-1111111111111111111;1&001,2,2,3,2,1,;3&002,6,12,1,;2&003,2,4,1,1,;2&004,3,6,1,1,;2&005,4,5,1,1,;2&006,5,12,1,1,;2&007,8,6,1,1,;2&008,8,13,1,1,;2&009,13,13,1,1,;2&010,8,2,1,1,;2&011,14,6,1,1,;2&012,16,10,1,1,;3&013,17,11,1,;2&014,17,11,1,1,;3&015,14,4,1,;2&016,4,10,1,1,;";
static std::string defLevelOutput3 = "0&1111111111111111111-1000101000000000201-1000101101111111111-1000101000110000011-1101101000110000011-1100001000110000011-1110101101111101111-1100101000000000111-1000101000001111111-1001101111000000011-1011000001111111011-1011111101000000001-1000000101000011111-1011111101111011111-1010000000000000001-1111111111111111111;1&001,2,2,3,;3&002,6,12,1,;2&003,2,4,1,1,;2&004,3,6,1,1,;2&005,4,5,1,1,;2&006,5,12,1,1,;2&007,8,6,1,1,;2&008,8,13,1,1,;2&009,13,13,1,1,;2&010,8,2,1,1,;2&011,14,6,1,1,;2&012,16,10,1,1,;3&013,17,11,1,;2&014,17,11,1,1,;3&015,14,4,1,;2&016,4,10,1,1,;";

HardCodedStorageManager::HardCodedStorageManager()
	: defaultLevel(true, defLevelLogic1, defLevelOutput1) //this is a member initialization list, otherwise the member defaultLevel requires a default constructor (with no arguments)
{
	//std::string("001/m&Default Map&0000-0110-0100-0000/m&0000-0110-0100-0000;";
}


HardCodedStorageManager::~HardCodedStorageManager()
{
}


StorageLevelData* HardCodedStorageManager::loadDefaultLevel() {
	StorageLevelData* defaultLevelCopy = new StorageLevelData(true, std::string(defLevelLogic1), std::string(defLevelOutput1)); //<TO DO JOSE> find out if this is actually a copy, create a test
	return defaultLevelCopy;
}

StorageGameData* HardCodedStorageManager::loadDefaultGame() {
	StorageGameData* defaultGame = new StorageGameData();
	defaultGame->add(new StorageLevelData(false, std::string(defLevelLogic1), std::string(defLevelOutput1)));
	defaultGame->add(new StorageLevelData(false, std::string(defLevelLogic2), std::string(defLevelOutput2)));
	defaultGame->add(new StorageLevelData(true, std::string(defLevelLogic3), std::string(defLevelOutput3)));
	return defaultGame;
}

