#pragma once
#include "IInputManager.h"
#include "UserInputType.h"
class RandomInputGenerator : public IInputManager
{
public:
	/// Test class
	RandomInputGenerator();
	~RandomInputGenerator();
	UserInputType getInput();
};

