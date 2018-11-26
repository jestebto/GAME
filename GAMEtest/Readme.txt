GAMEtest project will contain test classes and test methods with the purpose of testing the classes of GAMEsource project.
--------------------------------------------------------------

HOW TO RUN THE TESTS

Since GAMEsource is not a library project (it creates an executable instead), GAMEtest will fail to find the compiled
code to be tested.

So if you want to run the tests inside GAMEtest, you need to do the following steps:
	1. Righ-click in GAMEsource -> Properties
	2. Navigate to Configuration Properties -> General -> Project Defaults
	3. Set Configuration Type to "Static Library (.lib)"
	4. Apply and save the changes.

From the moment you do this, GAMEsource project will compile as static libraries (.lib) and you will not be able to run it.
However this will prevent the compilation of GAMEtest project to fail.

	5. Compile the GAMEtest project manually (see the next section of this Readme for why and how).
	6. Go to the menu Test -> Run -> All Tests (or simply run them from the Test Explorer window if you
	have already run them before).
	7. Once you are done running the tests, repeat steps 1-4 but set the Configuration Type to "Application (.exe)" instead.

--------------------------------------------------------------
HOW TO COMPILE THE TEST PROJECT

Why manually? Since trying to build both projects (while GAMEsource is delivering an .exe) would make the compiling of
GAMEtest fail, I have removed GAMEtest from the "Build Solution" command. This way you can continue working with the
perfectly functional GAMEsource project (.exe) without caring about compile errors.

For this reason, whenever you create new tests or pull a new version of GAMEtest from the git repo, you will need to
build this project manually:

	1. Place your pointer in the GAMEtest or any of its files, in the Solution Explorer.
	2. Go to the menu Build and click on Build GAMEtest.

OR
	1. Right-click GAMEtest project in the Solution Explorer.
	2. Click on Build.

This will manually build the GAMEtest project that has been excluded from the general Build Solution commmand. Now the tests
have been compiled and you are free to run them.
--------------------------------------------------------------