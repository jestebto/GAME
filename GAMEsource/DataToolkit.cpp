#include "DataToolkit.h"
#include <exception>
#include <stdexcept>


DataToolkit::DataToolkit()
{
}


DataToolkit::~DataToolkit()
{
}

std::vector<std::string> DataToolkit::getSubs(std::string s, char delimiter) {
	std::vector <std::string> subsVector; // Creating a vector which stores string values
	std::size_t del;
	if (s.back() != delimiter)throw std::runtime_error("DataToolkit: the final character of the string has to be the delimiter");

	for (unsigned int i{ 0 }; s.size() > 0; i++) {
		// find the symbol that separates objects (semicolon)
		del = s.find(delimiter);
		// store the data from the beggining of the string to the semicolon (not included)
		subsVector.push_back(s.substr(0, del));
		// delete the stored data and the semicolon
		s.erase(0, del + 1);
	}
	return subsVector;
}
