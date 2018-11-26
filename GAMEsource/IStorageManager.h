#pragma once
class IStorageManager
{
	/*
	* Interface to be implemented by a class acting as the manager of the Storage Component
	*/
public:
	virtual ~IStorageManager() = 0; //<COMMENT FOR MYSELF>virtual destructor to be implemented in the class implementing the interface
};