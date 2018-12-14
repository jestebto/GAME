#include "pch.h"
#include "StorageLevelData.h"


StorageLevelData::StorageLevelData(bool _isFinalLevel, std::string ld, std::string od)
{
	//Each row of data goes like (without spaces): ID / outputElementType & arg1 & arg2 &... / logicElementType & arg1 & arg2... ;
	/*The amount of arguments to be expected will depend on the element type
		//Output:
			type: m (map)
	*/
	this->isFinalLevel = _isFinalLevel;
	this->logicData = ld;
	this->outputData = od;
}


StorageLevelData::~StorageLevelData()
{
}

bool StorageLevelData::checkIsFinalLevel() {
	return this->isFinalLevel;
}
