#pragma once
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

