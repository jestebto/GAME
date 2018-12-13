#ifndef DATAUPDATE_H
#define DATAUPDATE_H

#include <string>

class DataUpdate
{
public:
	enum class ObjectType { PLAYER = 0 , ENEMY = 1, POWERUP = 2 };
	enum class Action { NOTHING = 0, ATTACK = 1, ELIMINATE = 2 };

	DataUpdate(std::string, int, int, std::string, ObjectType, Action);
	~DataUpdate();


	/// set the object's ID
	void setID(std::string);
	/// return the object's ID
	std::string getID();

	void setObjectXPosition(int);
	int getObjectXPosition();

	void setObjectYPosition(int);
	int getObjectYPosition();

	/// set the type of object
	void setObjectType(enum ObjectType);
	/// return objet type
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


#endif // !DATAUPDATE_H