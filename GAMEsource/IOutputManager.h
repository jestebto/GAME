#pragma once
#include "UserInputType.h"

class IOutputManager
{
	/*
	* Interface to be implemented by a class acting as the manager of the Output Component
	*/
public:
	virtual ~IOutputManager() = 0; ///virtual destructor to be implemented in the class implementing the interface
	virtual void update() = 0;
	virtual void updateTest(UserInputType) = 0;/// for test purposes to bypass the logic component 
};