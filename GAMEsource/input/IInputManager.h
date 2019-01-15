#ifndef IINPUTMANAGER_H
#define IINPUTMANAGER_H

#include "UserInputType.h"
#include "pch.h"

/// Interface to be implemented by a class acting as the manager of the Input Component. 
class IInputManager
{
	//<TO DO JOSE> find out if the destructor still needs to be =0 when the interface is properly implemented.
public:
	virtual ~IInputManager() = 0; //!< virtual destructor to be implemented in the class implementing the interface
	virtual UserInputType getInput() = 0; //!< Provides a single input from whichever source mapped as UserInputType
};

#endif /* IINPUTMANAGER_H */