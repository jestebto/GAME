#include "pch.h"
#include "RandomInputGenerator.h"
#include <cstdlib>

RandomInputGenerator::RandomInputGenerator()
{
}

RandomInputGenerator::~RandomInputGenerator()
{
}

UserInputType RandomInputGenerator::getInput()
{
	int input = rand()%5; //generates a random integer in the range [0,4]

	switch (input) {
	case 0:
		return UserInputType::Nothing;
	case 1:
		return UserInputType::Up;
	case 2:
		return UserInputType::Right;
	case 3:
		return UserInputType::Down;
	case 4:
		return UserInputType::Left;
	}
}
