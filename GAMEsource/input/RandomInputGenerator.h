#ifndef RANDOMINPUTMANAGER_H
#define RANDOMINPUTMANAGER_H

#include "IInputManager.h"
#include <cstdlib>
#include "pch.h"

class RandomInputGenerator : public IInputManager
{
public:
	/// Test class
	RandomInputGenerator();
	~RandomInputGenerator();
	UserInputType getInput();
};

#endif /* RANDOMINPUTMANAGER_H */