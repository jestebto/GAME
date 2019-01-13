#ifndef DATATOOLKIT_H
#define DATATOOLKIT_H

#include <vector>
#include <string>

/// A free class so that the different components read the hardcoded storage data in the same way
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

#endif /* DATATOOLKIT_H */

