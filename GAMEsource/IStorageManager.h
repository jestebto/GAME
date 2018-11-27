#pragma once
#include "StorageData.h"
class IStorageManager
{
	/*
	* Interface to be implemented by a class acting as the manager of the Storage Component
	*/
public:
	virtual ~IStorageManager() = 0; //virtual destructor to be implemented in the class implementing the interface
	virtual StorageData* loadDefaultLevel() = 0;
};