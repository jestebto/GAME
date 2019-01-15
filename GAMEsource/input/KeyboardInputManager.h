#ifndef KEYBOARDINPUTMANAGER_H
#define KEYBOARDINPUTMANAGER_H

#include "pch.h"
#include "IInputManager.h"
#include <SDL2/SDL.h>
#include <iostream>

///Gets input from the keyboard and mouse, and sends it through the IInputManager interface
class KeyboardInputManager : public IInputManager
{
public:
	KeyboardInputManager();
	~KeyboardInputManager();
	UserInputType getInput();
};

#endif /* KEYBOARDINPUTMANAGER_H */
