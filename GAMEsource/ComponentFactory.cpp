#include "pch.h"
#include "ComponentFactory.h"

//Storage managers:
#include "storage/HardCodedStorageManager.h"

//Input managers:
#include "input/KeyboardInputManager.h"
#include "input/RandomInputGenerator.h"

//Logic managers:
#include "logic/GameLevel.h"

//Output managers:
#include "output/GraphicOutputManager.h"

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
	return new KeyboardInputManager();
	//return new RandomInputGenerator();
}

ILogicManager* ComponentFactory::GetLogicManager()
{
	return new GameLevel();
}

IOutputManager* ComponentFactory::GetOutputManager()
{
	return new GraphicOutputManager();
}
