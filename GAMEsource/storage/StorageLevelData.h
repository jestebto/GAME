#ifndef STORAGELEVELDATA_H
#define STORAGELEVELDATA_H

#include <string>

/// Store data for a single level
class StorageLevelData
{
private:
	bool isFinalLevel; //!< is true if this is the final level
public:
	StorageLevelData(bool _isFinalLevel, std::string ld, std::string od); //!< ld=logicData, od = outputData
	~StorageLevelData();

	bool checkIsFinalLevel(); //!< return true if this is the final level
	std::string logicData; //!< mostly similar to output data, but can be different
	std::string outputData; //!< mostly similar to logic data, but can be different e.g. different textures that you can walk on
};

#endif /* STORAGELEVELDATA_H */