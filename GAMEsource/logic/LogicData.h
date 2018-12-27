#pragma once
#include <string>
class LogicData
{
	//This is going to be a data package created by GameManager, from StorageData, for ILogicManager
public:
	LogicData(std::string s);
	~LogicData();

	std::string data;   /// string with the data to create the level
};
