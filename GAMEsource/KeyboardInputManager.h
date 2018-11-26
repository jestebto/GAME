#pragma once
#include "IInputManager.h"
#include "UserInputType.h"

class KeyboardInputManager : public IInputManager
{
public:
	KeyboardInputManager();
	~KeyboardInputManager();
	UserInputType getInput();
};

