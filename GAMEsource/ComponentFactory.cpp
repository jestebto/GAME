#include "pch.h"
#include "ComponentFactory.h"

//Storage managers:
#include "HardCodedStorageManager.h"

//Input managers:
#include "KeyboardInputManager.h"
#include "RandomInputGenerator.h"

//Logic managers:

//Output managers:
#include "GraphicInterface.h"

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
	throw "Not implemented"; //George and Luuk: here you can return an instance of your Level class or however you want to call it
}

IOutputManager* ComponentFactory::GetOutputManager()
{
	//throw "Not implemented"; //Lior: here you can return an instance of your GraphicalInterface class or however you want to call it
	return new GraphicInterface();
}
