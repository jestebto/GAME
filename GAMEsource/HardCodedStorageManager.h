#pragma once
#include "IStorageManager.h"
#include "StorageData.h"
class HardCodedStorageManager : public IStorageManager
{
public:
	HardCodedStorageManager();
	~HardCodedStorageManager();
	StorageData* loadDefaultLevel();

private:
	StorageData defaultLevel;
};

