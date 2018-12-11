#include "DataUpdate.h"



DataUpdate::DataUpdate(std::string id, int x, int y, std::string data, DataUpdate::ObjectType type, DataUpdate::Action action)
{
	objectID = id;
	xPosition = x;
	yPosition = y;
	objectData = data;
	objectType = type;
	objectAction = action;
}


DataUpdate::~DataUpdate()
{
}

void DataUpdate::setID(std::string id) { objectID = id; }

std::string DataUpdate::getID() { return objectID; }

void DataUpdate::setObjectXPosition(int x) { xPosition = x; }
int DataUpdate::getObjectXPosition() { return xPosition; }

void DataUpdate::setObjectYPosition(int x) { yPosition = x; }
int DataUpdate::getObjectYPosition() { return yPosition; }

void DataUpdate::setData(std::string data) { objectData = data; }

std::string DataUpdate::getData() { return objectData; }

void DataUpdate::setAction(DataUpdate::Action action) { objectAction = action; }

DataUpdate::Action DataUpdate::getAction() { return objectAction; }

void DataUpdate::setObjectType(DataUpdate::ObjectType type) { objectType = type; }

DataUpdate::ObjectType DataUpdate::getObjectType() { return objectType; }
