#include "pch.h"
#include "StorageData.h"


StorageData::StorageData(std::string ld, std::string od)
{
	//Each row of data goes like (without spaces): ID / outputElementType & arg1 & arg2 &... / logicElementType & arg1 & arg2... ;
	/*The amount of arguments to be expected will depend on the element type
		//Output:
			type: m (map)
	*/
	
	this->logicData = ld;
	this->outputData = od;
}


StorageData::~StorageData()
{
}
