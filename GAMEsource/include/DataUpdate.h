#pragma once

#include <string>
/**
* A free class which allows the ILogicManager to send updates through the GameManger to the IOutputManager  side
*
*/
class DataUpdate
{
public:
	enum class ObjectType { PLAYER = 0 , ENEMY = 1, POWERUP = 2 };
	enum class Action { NOTHING = 0, ATTACK = 1, ELIMINATE = 2, GET_HIT };

	// Constructor
	DataUpdate(std::string, int, int, std::string, ObjectType, Action);

	//Destructor
	~DataUpdate();


	/// set the object's ID
	void setID(std::string);

	/// return the object's ID
	std::string getID();

	// set the object's x Position
	void setObjectXPosition(int);

	// get the object's x Position
	int getObjectXPosition();

	// set the object's y Position
	void setObjectYPosition(int);

	// set the object's y Position
	int getObjectYPosition();

	/// set the type of object
	void setObjectType(enum ObjectType);

	/// return object type
	enum ObjectType getObjectType();

	/// store the data
	void setData(std::string);

	/// return data
	std::string getData();

	/// set action
	void setAction(Action);
	/// return action
	enum Action getAction();

private:
	std::string objectID;
	int xPosition;
	int yPosition;
	std::string objectData;
	ObjectType objectType;
	Action objectAction;
};


