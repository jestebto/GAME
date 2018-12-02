#pragma once
#include <string>

class StorageData
{
public:
	StorageData(std::string ld, std::string od);
	~StorageData();

	std::string logicData;
	std::string outputData;
};

