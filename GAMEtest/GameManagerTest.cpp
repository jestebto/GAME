#include "stdafx.h"
#include "CppUnitTest.h"
#include "../GAMEsource/GameManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GAMEtest
{
	TEST_CLASS(GameManagerTest) //For simplicity, if you want to test class MyClass, name the test class MyClassTest
	{
	public:

		TEST_METHOD(main_Add_1_plus_1_equals_2) //give whatever meaningful name you want to your new test method
		{
			//This method tests that GameManager::Add(...) function is returning the right value

			//Arrange: this is where you prepare what you need for testing (for example creating objects)
			int num1 = 1, num2 = 1, num3;

			/*
			Act: this is where you execute the specific thing you want to test
			(for example executing the function that you want to test).
			*/
			num3 = GameManager::Add(num1, num2);

			/*
			Assert: this is where you compare the expected and actual results with the corresponding Assert function (for
			example comparing the stored output of a function with the expected value)
			*/
			Assert::AreEqual(2, num3); //Expected: 2, actual: value stored in num3. Let's execute it and see if they are equal.
		}

		TEST_METHOD(main_Add_1_plus_minus1_equals_0) //Keep the Arrange, Act, Assert comments in your new tests to make it more readable
		{
			//Arrange
			int num1 = 1, num2 = -1, num3;

			//Act
			num3 = GameManager::Add(num1, num2);

			//Assert
			Assert::AreEqual(0, num3);
		}

	};
}