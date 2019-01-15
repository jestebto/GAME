#ifndef LOGICDATA_H
#define LOGICDATA_H
///This is going to be a data package created by GameManager, from StorageData, for ILogicManager
#include <string>
class LogicData
{
public:
	LogicData(std::string s);
	~LogicData();

	std::string data;   ///< string with the data to create the level
};

#endif /* LOGICDATA_H */

