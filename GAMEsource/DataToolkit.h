#pragma once
#include <vector>
#include <string>

class DataToolkit
{
public:
	/// constructor
	DataToolkit();
	/// destructor 
	~DataToolkit();
	/// devide a string into substrings
	static std::vector<std::string> getSubs(std::string s, char delimiter);
};

