#pragma once
#include "UserInputType.h"
#include "OutputData.h"
#include "DataUpdate.h"

#include <vector>
#include <string>


class IOutputManager
{
	/**
	* Interface to be implemented by a class acting as the manager of the Output Component
	*/
public:
	virtual ~IOutputManager() = 0; //!<virtual destructor to be implemented in the class implementing the interface
	virtual void loadLevel(OutputData) = 0;//!< initialise SDL screen, read input data and create the maps and gamesprites in use
	virtual void update(std::vector<std::shared_ptr<DataUpdate>>) = 0; //!< update the screen based on the game state as determined by the logic manager
	virtual void update(UserInputType) = 0;//!< for test purposes to bypass the logic component 
	virtual void showGameOverScreen() = 0;
	//virtual void showVictoryScreen() = 0; //!<future implementation, you can prepare for it from the child class
}; 