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
	throw "Not implemented"; //George and Luuk: here you can return an instance of your Level class or however you want to call it
}

IOutputManager* ComponentFactory::GetOutputManager()
{
	throw "Not implemented"; //Lior: here you can return an instance of your GraphicalInterface class or however you want to call it
}
