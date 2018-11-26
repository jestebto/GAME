#pragma once
#include "IInputManager.h"
#include "UserInputType.h"
class RandomInputGenerator : public IInputManager
{
public:
	RandomInputGenerator();
	~RandomInputGenerator();
	UserInputType getInput();
};

