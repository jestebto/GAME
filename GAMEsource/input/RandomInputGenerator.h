#ifndef RANDOMINPUTMANAGER_H
#define RANDOMINPUTMANAGER_H

#include "IInputManager.h"
#include <cstdlib>
#include "pch.h"
/// Test class
class RandomInputGenerator : public IInputManager
{
public:
	RandomInputGenerator();
	~RandomInputGenerator();
	UserInputType getInput();
};

#endif /* RANDOMINPUTMANAGER_H */