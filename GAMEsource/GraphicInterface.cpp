/*
 *  Created on: 28 November, 2018
 *      Author: Lior Sinai
 * Description: See GraphicInterface.h
 */

#include "GraphicInterface.h"
#include <iostream>
#include "UserInputType.h"
#include "DataToolkit.h"


GraphicInterface::GraphicInterface()
{
	//All setup is done in GrahpicInterface::loadlevel once data has been received
}


GraphicInterface::~GraphicInterface()
{
	SDL_DestroyTexture(sheet);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GraphicInterface::loadLevel(OutputData inputString) {
	using namespace SpriteAttributes;

	//Parse data
	std::vector <std::string> objectVector; // temporary string for storing the current object
	// getSubs function creates a vector of string corresponding to different objects
	objectVector = DataToolkit::getSubs(inputString.data, ';');
	std::vector <std::string> tempConstructorData;

	for (unsigned int i{ 0 }; i < objectVector.size(); ++i) {
		std::size_t amp = objectVector[i].find("&"); //<TO DO> check if we can specify a specific type

		std::string initialChar{ objectVector[i].at(0) }; // String containing the first character of a string 
		int objectType{ stoi(initialChar) }; // Conv is the integer corresponding to the first character of a string

		switch (objectType) {
		case 0: { // 0 is map
			// erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);
			setBackground(objectVector[i]);
			break;
		}
		case 1: { //1 is player
		//erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);
			//separate the data to construct the new object
			tempConstructorData = DataToolkit::getSubs(objectVector[i],',');

			this->spriteObjects[tempConstructorData[0]] = new GameSprite{ "Player", stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), PACMAN, RIGHT };

			tempConstructorData = {}; //make sure the vector is empty in the next case <TO DO> make sure if this is needed
			break;
		}
		case 2: { // 2 is an enemy
			// erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);
			// separate the data to construct the new object
			tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');
			// create a new enemy storing a shared pointer to it
			this->spriteObjects[tempConstructorData[0]] = new GameSprite{ "Enemy", stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), SCAREDINV, UP };

			tempConstructorData = {}; // make sure the vector is empty in the next case
			break;
		}
		}
	}


	//Hard coded board for test purposes
	/*
	std::vector<std::vector<int>> board = { {
		#include "board.def"
	} };
	this->map = std::move(board);
	*/

	this->mapWidth = map[0].size();
	this->mapHeight = map.size();
	// Initialize and load textures.
	this->init(); //indexing starts at 0 so minus 1
	this->loadTextures();

	//this->spriteObjects["099"] = new GameSprite{ "Test", 1, 1, CLYDE, UP };

	//On the first iteration, only draw the background:

	// Clear the current renderer.
	SDL_RenderClear(renderer);
	// Draw the walls.
	drawBackground(map);
	// Update the screen.
	SDL_RenderPresent(renderer);
}

void GraphicInterface::setBackground(const std::string& mapString) {
	//loop through the map data
	unsigned int row{ 0 };
	unsigned int column{ 0 };
	map.push_back(std::vector<int>());
	for (unsigned int value{ 0 }; value < mapString.length(); value++) {
		int tempValue = mapString.at(value);

		if (tempValue == 45) { //!< if dash, add row
			column = 0;
			row++;
			map.push_back(std::vector<int>());
		}
		else {
			map[row].push_back(tempValue - 48);
			column++;
		}
	}
}


void GraphicInterface::update(std::vector<std::string> data)
{
	// Clear the current renderer.
	SDL_RenderClear(renderer);

	// Draw the walls.
	drawBackground(map);

	// Update the map based on the incoming data
	// Format is {"ID,x,y"},{"ID,x,y"},...
	std::vector <std::string> tempConstructorData;
	for (const std::string &stringData : data){
		tempConstructorData = DataToolkit::getSubs(stringData, ',');

		// Look up in the ID in the sprite map
		auto mapPair = spriteObjects.find(tempConstructorData[0]);

		if (mapPair == spriteObjects.end())
			std::cout << "Element not found" << '\n';
		else {
			moveSprite(mapPair->second, stoi(tempConstructorData[1]), stoi(tempConstructorData[2]));
		}

	}

	// Loop through all the objects and draw them.
	for (auto &mapPair : this->spriteObjects) {
		int x = mapPair.second->getXPosition();
		int y = mapPair.second->getYPosition();

		SDL_Rect dst = { x * TILESIZE, y * TILESIZE, TILESIZE,
						TILESIZE };
		SDL_RenderCopy(renderer, sheet, &tileSet[mapPair.second->art][mapPair.second->direction],
			&dst);
	}

	// Draw the lives.
	drawLives();

	// Update the screen.
	SDL_RenderPresent(renderer);
}

void GraphicInterface::update(std::vector<std::shared_ptr<DataUpdate>> data)
{
	// Clear the current renderer.
	SDL_RenderClear(renderer);

	// Draw the walls.
	drawBackground(map);

	// Update the map based on the incoming data
	// Format is {"ID,x,y"},{"ID,x,y"},...


	for (std::shared_ptr<DataUpdate> &dataPtr : data) {


		// Look up in the ID in the sprite map
		auto mapPair = spriteObjects.find(dataPtr->getID());

		if (mapPair == spriteObjects.end())
			std::cout << "Element not found" << '\n';
		else {
			moveSprite(mapPair->second, dataPtr->getObjectXPosition(), dataPtr->getObjectYPosition());
		}

	}

	// Loop through all the objects and draw them.
	for (auto &mapPair : this->spriteObjects) {
		int x = mapPair.second->getXPosition();
		int y = mapPair.second->getYPosition();

		SDL_Rect dst = { x * TILESIZE, y * TILESIZE, TILESIZE,
						TILESIZE };
		SDL_RenderCopy(renderer, sheet, &tileSet[mapPair.second->art][mapPair.second->direction],
			&dst);
	}

	// Draw the lives.
	drawLives();

	// Update the screen.
	SDL_RenderPresent(renderer);
}

void GraphicInterface::update(UserInputType userInput)
{
	// Clear the current renderer.
	SDL_RenderClear(renderer);

	// Draw the walls.
	drawBackground(map);
	
	GraphicInterface::moveSprite(userInput, "001");

	// Loop through all the objects and draw them.
	for (auto &mapPair : this->spriteObjects) {
		int x = mapPair.second->getXPosition();
		int y = mapPair.second->getYPosition();

		SDL_Rect dst = { x * TILESIZE, y * TILESIZE, TILESIZE,
						TILESIZE };
		SDL_RenderCopy(renderer, sheet, &tileSet[mapPair.second->art][mapPair.second->direction],
			&dst);
	}
	

	// Update the screen.
	SDL_RenderPresent(renderer);
}

void GraphicInterface::showGameOverScreen() {
	using namespace SpriteAttributes;
	SDL_Rect dst = { 0, 0 , (mapWidth+1)*TILESIZE, (mapHeight+1)*TILESIZE };
	
	// Clear the current renderer.
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, gameOverScreen, NULL, &dst);//NULL to show the entire structure

	// Update the screen.
	SDL_RenderPresent(renderer);
}

void GraphicInterface::moveSprite(GameSprite* element, int x, int y)
{
	// move a Sprite to a position
	using namespace SpriteAttributes;

	int x_old = element->getXPosition();
	int y_old = element->getYPosition();

	element->setXPosition(x);
	element->setYPosition(y);
	if (y_old < y) // moving DOWN
	{
		element->direction = DOWN;
	}
	else if (y_old > y) //moving UP
	{
		element->direction = UP;
	}
	if (x_old < x) //moving right
	{
		element->direction = RIGHT;
	}
	else if (x_old > x) //moving left
	{
		element->direction = LEFT;
	}

}


void GraphicInterface::moveSprite(UserInputType command, std::string ID)
{
	// directly move a Sprite based on user input
	// for test purposes only, as this is not connected to the logic
	using namespace SpriteAttributes;
	

	int moveSize= 1;
	/*  Co-ordinates:
	*   .---> +x
	*   |
	*   v
	*   +y
    */

	auto mapPair = spriteObjects.find(ID);

	if (mapPair == spriteObjects.end())
		std::cout << "Element not found" << '\n';
	else
	{
		GameSprite* &element= mapPair->second;
			switch (command) {
			case UserInputType::Up:
				element->setYPosition(element->getYPosition() - moveSize);
				element->direction = UP; //for display purposes only
				break;
			case UserInputType::Down:
				element->setYPosition(element->getYPosition() + moveSize);
				element->direction = DOWN; //for display purposes only
				break;
			case UserInputType::Left:
				element->setXPosition(element->getXPosition() - moveSize);
				element->direction = LEFT; //for display purposes only
				break;
			case UserInputType::Right:
				element->setXPosition(element->getXPosition() + moveSize);
				element->direction = RIGHT; //for display purposes only
				break;
			default:
				//Do nothing
				break;
			}
	}
	
}

/// Initialises the UI::window and the UI::renderer.
void GraphicInterface::init()
{
	// Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create a Window in the middle of the screen
	window = SDL_CreateWindow("The Awesome Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, mapWidth * TILESIZE,
		mapHeight * TILESIZE + (TILESIZE + 4), SDL_WINDOW_SHOWN);

	// Create a new renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
}

/// From the Pacman Code
void GraphicInterface::loadTextures()
{
	// Load sprite sheet
	sheet = this->loadTexture("resources/sam_gfx.bmp");
	seperateTiles();

	gameOverScreen = this->loadTexture("resources/GAME_OVER.bmp");
}

/// From the Pacman Code
void GraphicInterface::seperateTiles()
{	
	
	using namespace SpriteAttributes;
	const int size = TILESIZE;
	const int o = 4; // offset in bitmap (both in x and y)
	std::map<Direction, SDL_Rect> pacman;
	//                    x              y      width,height
	pacman[UP] = { o + size * 1, o + size * 11, size, size };
	pacman[DOWN] = { o + size * 13, o + size * 7, size, size };
	pacman[LEFT] = { o + size * 0, o + size * 11, size, size };
	pacman[RIGHT] = { o + size * 12, o + size * 7, size, size };
	tileSet[PACMAN] = pacman;

	std::map<Direction, SDL_Rect> pinky;
	pinky[UP] = { o + size * 6, o + size * 9, size, size };
	pinky[DOWN] = { o + size * 2, o + size * 9, size, size };
	pinky[RIGHT] = { o + size * 0, o + size * 9, size, size };
	pinky[LEFT] = { o + size * 4, o + size * 9, size, size };
	tileSet[PINKY] = pinky;

	std::map<Direction, SDL_Rect> blinky;
	blinky[UP] = { o + size * 6, o + size * 7, size, size };
	blinky[DOWN] = { o + size * 2, o + size * 7, size, size };
	blinky[RIGHT] = { o + size * 0, o + size * 7, size, size };
	blinky[LEFT] = { o + size * 4, o + size * 7, size, size };
	tileSet[BLINKY] = blinky;

	std::map<Direction, SDL_Rect> clyde;
	clyde[UP] = { o + size * 6, o + size * 10, size, size };
	clyde[DOWN] = { o + size * 2, o + size * 10, size, size };
	clyde[RIGHT] = { o + size * 0, o + size * 10, size, size };
	clyde[LEFT] = { o + size * 4, o + size * 10, size, size };
	tileSet[CLYDE] = clyde;

	std::map<Direction, SDL_Rect> inky;
	inky[UP] = { o + size * 14, o + size * 9, size, size };
	inky[DOWN] = { o + size * 10, o + size * 9, size, size };
	inky[LEFT] = { o + size * 12, o + size * 9, size, size };
	inky[RIGHT] = { o + size * 8, o + size * 9, size, size };
	tileSet[INKY] = inky;

	std::map<Direction, SDL_Rect> scared;
	scared[UP] = { o + size * 12, o + size * 6, size, size };
	scared[DOWN] = scared[UP];
	scared[LEFT] = scared[UP];
	scared[RIGHT] = scared[UP];
	tileSet[SCARED] = scared;

	std::map<Direction, SDL_Rect> scaredinv;
	scaredinv[UP] = { o + size * 4, o + size * 11, size, size };
	scaredinv[DOWN] = scaredinv[UP];
	scaredinv[LEFT] = scaredinv[UP];
	scaredinv[RIGHT] = scaredinv[UP];
	tileSet[SCAREDINV] = scaredinv;

	std::map<Direction, SDL_Rect> strawberry;
	strawberry[UP] = { o + size * 1, o + size * 5, size, size };
	strawberry[DOWN] = strawberry[UP];
	strawberry[LEFT] = strawberry[UP];
	strawberry[RIGHT] = strawberry[UP];
	tileSet[STRAWBERRY] = strawberry;

	std::map<Direction, SDL_Rect> cherry;
	cherry[UP] = { o + size * 0, o + size * 5, size, size };
	cherry[DOWN] = cherry[UP];
	cherry[LEFT] = cherry[UP];
	cherry[RIGHT] = cherry[UP];
	tileSet[CHERRY] = cherry;

	std::map<Direction, SDL_Rect> orange;
	orange[UP] = { o + size * 2, o + size * 5, size, size };
	orange[DOWN] = orange[UP];
	orange[LEFT] = orange[UP];
	orange[RIGHT] = orange[UP];
	tileSet[ORANGE] = orange;

	std::map<Direction, SDL_Rect> lemon;
	lemon[UP] = { o + size * 3, o + size * 5, size, size };
	lemon[DOWN] = lemon[UP];
	lemon[LEFT] = lemon[UP];
	lemon[RIGHT] = lemon[UP];
	tileSet[LEMON] = lemon;

	std::map<Direction, SDL_Rect> apple;
	apple[UP] = { o + size * 4, o + size * 5, size, size };
	apple[DOWN] = apple[UP];
	apple[LEFT] = apple[UP];
	apple[RIGHT] = apple[UP];
	tileSet[APPLE] = apple;

	std::map<Direction, SDL_Rect> grapes;
	grapes[UP] = { o + size * 5, o + size * 5, size, size };
	grapes[DOWN] = grapes[UP];
	grapes[LEFT] = grapes[UP];
	grapes[RIGHT] = grapes[UP];
	tileSet[GRAPES] = grapes;

	std::map<Direction, SDL_Rect> dot;
	dot[UP] = { o + 12 * 16, o + 12 * 0, size / 2, size / 2 };
	dot[DOWN] = dot[UP];
	dot[LEFT] = dot[UP];
	dot[RIGHT] = dot[UP];
	tileSet[DOT] = dot;

	std::map<Direction, SDL_Rect> energizer;
	energizer[UP] = { o + 12 * 18, o + 12 * 0, size / 2, size / 2 };
	energizer[DOWN] = energizer[UP];
	energizer[LEFT] = energizer[UP];
	energizer[RIGHT] = energizer[UP];
	tileSet[ENERGIZER] = energizer;

	std::map<Direction, SDL_Rect> wall;
	wall[UP] = { o + size * 6, o + size * 11, size, size };
	wall[DOWN] = wall[UP];
	wall[LEFT] = wall[UP];
	wall[RIGHT] = wall[UP];
	tileSet[WALL] = wall;

	std::map<Direction, SDL_Rect> key;
	key[UP] = { o + size * 7, o + size * 5, size, size };
	key[DOWN] = key[UP];
	key[LEFT] = key[UP];
	key[RIGHT] = key[UP];
	tileSet[KEY] = key;

	for (int i = 0; i < 10; i++) {
		std::map<Direction, SDL_Rect> nr;
		nr[UP] = { o + (size / 2) * i, o + 1 + size * 0, size / 2, size / 2 };
		nr[DOWN] = nr[UP];
		nr[LEFT] = nr[UP];
		nr[RIGHT] = nr[UP];
		tileSet[(ArtType)(ZERO + i)] = nr;
	}
}

/// From the Pacman Code
void GraphicInterface::drawBackground(std::vector<std::vector<int>> &map)
{
	using namespace SpriteAttributes;
	// Draw a wall on each position containing a one
	for (size_t i = 0; i < map.size(); i++) {
		for (size_t j = 0; j < map[i].size(); j++) {
			if (map[i][j] == 1) {
				SDL_Rect dst = { static_cast<int>(j) * TILESIZE,
								static_cast<int>(i) * TILESIZE, TILESIZE,
								TILESIZE };
				SDL_RenderCopy(renderer, sheet, &tileSet[WALL][DOWN], &dst);
			}
			else if (map[i][j] == 2) {
				SDL_Rect dst = { static_cast<int>(j) * TILESIZE,
								static_cast<int>(i) * TILESIZE, TILESIZE,
								TILESIZE };
				SDL_RenderCopy(renderer, sheet, &tileSet[KEY][DOWN], &dst);
			}
		}
	}
}

/// Draws an amount of pacmans corresponding to the amount of lives
// From the Pacman Code
void GraphicInterface::drawLives()
{
	using namespace SpriteAttributes;
	for (int i = 0; i < lives; i++) {
		SDL_Rect dst = { mapHeight * TILESIZE - i * TILESIZE, mapHeight * TILESIZE, TILESIZE,
						TILESIZE };
		SDL_RenderCopy(renderer, sheet, &tileSet[PACMAN][LEFT], &dst);
	}
}

// From the Pacman Code
SDL_Texture *GraphicInterface::loadTexture(const std::string &file)
{
	SDL_Surface *surf = SDL_LoadBMP(file.c_str());
	if (surf == nullptr) {
		std::cerr << "Error while loading texture bitmap: " << SDL_GetError() << std::endl;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr) {
		std::cerr << "Error while creating texture: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surf);
	return texture;
}



