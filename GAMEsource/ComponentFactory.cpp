#include "pch.h"
#include "ComponentFactory.h"

//Storage managers:
#include "HardCodedStorageManager.h"

//Input managers:
#include "KeyboardInputManager.h"
#include "RandomInputGenerator.h"

//Logic managers:
#include "GameLevel.h"

//Output managers:


ComponentFactory::ComponentFactory()
{

}


ComponentFactory::~ComponentFactory()
{

}

IStorageManager* ComponentFactory::GetStorageManager()
{
	return new HardCodedStorageManager();
}

IInputManager* ComponentFactory::GetInputManager()
{
	//return new KeyboardInputManager();
	return new RandomInputGenerator();
}

ILogicManager* ComponentFactory::GetLogicManager()
{
	return new GameLevel();
}

IOutputManager* ComponentFactory::GetOutputManager()
{
	throw "Not implemented"; //Lior: here you can return an instance of your GraphicalInterface class or however you want to call it
}
