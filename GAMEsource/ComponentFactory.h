#ifndef COMPONENTFACTORY_H
#define COMPONENTFACTORY_H
#include "storage/IStorageManager.h"
#include "input/IInputManager.h"
#include "logic/ILogicManager.h"
#include "output/IOutputManager.h"

/**
The purpose of this class is to determine which specific implementations of the components to be used.
Example: GetStorageComponent might return a HardCodedStorageManager, or a FileSystemStorageManager, which
both implement the IStorageManager interface.
*/
class ComponentFactory
{
public:
	ComponentFactory();
	~ComponentFactory();

	IStorageManager* GetStorageManager(); //!< will return a pointer to an object implementing the IStorageManager
	IInputManager* GetInputManager();	//!< will return a pointer to an object implementing the IInputManager
	ILogicManager* GetLogicManager();	//!< will return a pointer to an object implementing the ILogicManager
	IOutputManager* GetOutputManager(); //!< will return a pointer to an object implementing the IOutputManager
};

#endif /* COMPONENTFACTORY_H */

