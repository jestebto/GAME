#pragma once
#include "UserInputType.h"
#include "LogicData.h"
#include "DataUpdate.h"
#include <vector>
#include <string>

class ILogicManager
{
	/*
	* Interface to be implemented by a class acting as the manager of the Logic Component
	*/
public:
	virtual ~ILogicManager() = 0; //virtual destructor to be implemented in the class implementing the interface
	virtual void createLevel(LogicData level) = 0; /// create game level
	virtual void executeUserCommand(UserInputType input) = 0; /// execute the users input
	virtual std::vector<std::shared_ptr<DataUpdate>> getLevelState() = 0; /// get objec's data as a vector of strings
	virtual bool checkGameOver() = 0 ; /// check if the game is over
};