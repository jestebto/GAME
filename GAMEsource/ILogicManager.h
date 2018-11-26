#pragma once
#include "UserInputType.h"
class ILogicManager
{
	/*
	* Interface to be implemented by a class acting as the manager of the Logic Component
	*/
public:
	virtual ~ILogicManager() = 0; //<COMMENT FOR MYSELF>virtual destructor to be implemented in the class implementing the interface
	virtual void executeUserCommand(UserInputType input) = 0;
};