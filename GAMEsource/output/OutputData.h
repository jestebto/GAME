#ifndef OUTPUTDATA_H
#define OUTPUTDATA_H

#include <string>

///This is going to be a data package created by GameManager, from StorageData, for IOutputManager
class OutputData
{
public:
	OutputData(std::string); 
	~OutputData();

	std::string data; ///< string data given in a special format for loading each level
};

#endif /* OUTPUTDATA_H */