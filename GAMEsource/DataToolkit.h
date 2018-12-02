#pragma once
#include <vector>
#include <string>

class DataToolkit
{
public:
	DataToolkit();
	~DataToolkit();
	static std::vector<std::string> getSubs(std::string s, char delimiter);
};

