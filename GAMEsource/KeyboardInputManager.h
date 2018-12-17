#pragma once
#include "IInputManager.h"
#include "UserInputType.h"

/**
* Gets input from the keyboard and mouse, and sends it through the IInputManager interface
*/
class KeyboardInputManager : public IInputManager
{
public:
	KeyboardInputManager();
	~KeyboardInputManager();
	UserInputType getInput();
};

