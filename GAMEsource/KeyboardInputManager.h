#pragma once
#include "IInputManager.h"

class KeyboardInputManager : public IInputManager
{
public:
	KeyboardInputManager();
	~KeyboardInputManager();
	UserInputType getInput();
};

