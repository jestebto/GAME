#include "DataUpdate.h"



DataUpdate::DataUpdate(std::string id, std::string data, DataUpdate::ObjectType type, DataUpdate::Action action)
{
	objectID = id;
	objectData = data;
	objectType = type;
	objectAction = action;
}


DataUpdate::~DataUpdate()
{
}

void DataUpdate::setID(std::string id) { objectID = id; }

std::string DataUpdate::getID() { return objectID; }

void DataUpdate::setData(std::string data) { objectData = data; }

std::string DataUpdate::getData() { return objectData; }

void DataUpdate::setAction(DataUpdate::Action action) { objectAction = action; }

DataUpdate::Action DataUpdate::getAction() { return objectAction; }

void DataUpdate::setObjectType(DataUpdate::ObjectType type) { objectType = type; }

DataUpdate::ObjectType DataUpdate::getObjectType() { return objectType; }
