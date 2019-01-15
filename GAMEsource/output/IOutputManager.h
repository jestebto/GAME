#ifndef IOUTPUTMANAGER_H
#define IOUTPUTMANAGER_H

#include "UserInputType.h"
#include "OutputData.h"
#include "DataUpdate.h"

#include <vector>
#include <string>
#include <memory>

/**
* Interface to be implemented by a class acting as the manager of the Output Component
*/
class IOutputManager
{
public:
	virtual ~IOutputManager() = 0; //!<virtual destructor to be implemented in the class implementing the interface
	virtual void loadLevel(OutputData) = 0;//!< initialise SDL screen, read input data and create the maps and gamesprites in use
	virtual void update(std::vector<std::shared_ptr<DataUpdate>>) = 0; //!< update the screen based on the game state as determined by the logic manager
	virtual void update(UserInputType) = 0;//!< for test purposes to bypass the logic component 
	virtual void showGameOverScreen() = 0;  //!< show Game Over Screen
	virtual void showVictoryScreen() = 0;   //!< show Victory Screen
	virtual void showGenericErrorScreen() = 0; //!< show Generic Error Screen
}; 

#endif /* IOUTPUTMANAGER_H */