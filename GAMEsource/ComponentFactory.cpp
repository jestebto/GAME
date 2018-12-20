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
#include "GraphicOutputManager.h"

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
