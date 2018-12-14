#pragma once
#include <string>

class StorageLevelData
{
private:
	bool isFinalLevel;
public:
	StorageLevelData(bool _isFinalLevel, std::string ld, std::string od);
	~StorageLevelData();

	bool checkIsFinalLevel();
	std::string logicData;
	std::string outputData;
};

