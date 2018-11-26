#include "pch.h"
#include "ComponentFactory.h"

//Storage managers:

//Input managers:
#include "KeyboardInputManager.h"
#include "RandomInputGenerator.h"

//Logic managers:

//Output managers:


ComponentFactory::ComponentFactory()
{

}


ComponentFactory::~ComponentFactory()
{
	throw "Not implemented";
}

IStorageManager* ComponentFactory::GetStorageManager()
{
	throw "Not implemented";
}

IInputManager* ComponentFactory::GetInputManager()
{
	//return new KeyboardInputManager();
	return new RandomInputGenerator();
}

ILogicManager* ComponentFactory::GetLogicManager()
{
	throw "Not implemented";
}

IOutputManager* ComponentFactory::GetOutputManager()
{
	throw "Not implemented";
}
