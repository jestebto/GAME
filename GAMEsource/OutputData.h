#pragma once
#include <string>
class OutputData
{
	///This is going to be a data package created by GameManager, from StorageData, for IOutputManager
public:
	OutputData(std::string); 
	~OutputData();

	std::string data; ///< string data given in a special format for loading each level
};

