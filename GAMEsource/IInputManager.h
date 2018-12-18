#pragma once
#include "UserInputType.h"
class IInputManager
{
	/*
	* Interface to be implemented by a class acting as the manager of the Input Component
	*/
	//<TO DO JOSE> find out if the destructor still needs to be =0 when the interface is properly implemented.
public:
	virtual ~IInputManager() = 0; //!< virtual destructor to be implemented in the class implementing the interface
	virtual UserInputType getInput() = 0; //!< Provides a single input from whichever source mapped as UserInputType
};