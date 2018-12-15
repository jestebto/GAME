/*
 *  Created on: 28 November, 2018
 *      Author: Lior Sinai
 * Description: See GraphicInterface.h
 */

#include "GraphicOutputManager.h"

GraphicOutputManager::GraphicOutputManager()
{
	//spriteManager = new SpriteManager(24);
	spriteManager = std::make_unique<SpriteManager>();

	// Initialize window and load textures.
	this->init();
	this->loadTextures();
	//All other setup is done in GrahpicInterface::loadlevel once data has been received
}


GraphicOutputManager::~GraphicOutputManager()
{
	//SDL_DestroyTexture(sheet);
	SDL_DestroyTexture(gameOverScreen);
	SDL_DestroyTexture(victoryScreen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GraphicOutputManager::loadLevel(OutputData inputString) {
	//TO DO LIOR: clear out all pre-existing data when this is called. Then remove the reinstantiation from GameManager (inside the Update() method, we want to call to ComponentFactory->getOutputManager() )
	using namespace SpriteAttributes;

	spriteObjects.clear();
	levelMap.clear();

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

			this->spriteObjects[tempConstructorData[0]] = std::make_unique<GameSprite> (DataUpdate::ObjectType::PLAYER, stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), PACMAN, CharacterOrientation::Down );
			this->lives= stoi(tempConstructorData[3]);

			tempConstructorData = {}; //make sure the vector is empty in the next case <TO DO> make sure if this is needed
			break;
		}
		case 2: { // 2 is an enemy
			// erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);
			// separate the data to construct the new object
			tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');
			// create a new enemy storing a shared pointer to it
			this->spriteObjects[tempConstructorData[0]] = std::make_unique<GameSprite>( DataUpdate::ObjectType::ENEMY, stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), SCAREDINV, CharacterOrientation::Up );

			tempConstructorData = {}; // make sure the vector is empty in the next case
			break;
		}
		case 3: { // 3 is a power up
		// erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);
			// separate the data to construct the new object
			tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');

			// Format is {ID,x,y,lives}
			this->spriteObjects[tempConstructorData[0]] = std::make_unique<GameSprite>( DataUpdate::ObjectType::POWERUP, stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), APPLE, CharacterOrientation::Up);
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

	//On the first iteration, only draw the background:

	// Clear the current renderer.
	SDL_RenderClear(renderer);
	// Draw the walls.
	drawBackground(levelMap);
	// Update the screen.
	SDL_RenderPresent(renderer);
}

void GraphicOutputManager::setBackground(const std::string& mapString) {
	//loop through the map data
	unsigned int row{ 0 };
	unsigned int column{ 0 };
	levelMap.push_back(std::vector<int>());
	for (unsigned int value{ 0 }; value < mapString.length(); value++) {
		int tempValue = mapString.at(value);

		if (tempValue == 45) { //!< if dash, add row
			column = 0;
			row++;
			levelMap.push_back(std::vector<int>());
		}
		else {
			levelMap[row].push_back(tempValue - 48);
			column++;
		}
	}
	// xOffset = screenWidth/2 - mapWidth/2;
	this->xOffset = (SCREEN_WIDTH - static_cast<int>( levelMap[0].size() ))/ 2;
	// yOffset = screenHeight/2 - mapWidth/2;
	this->yOffset = (SCREEN_HEIGHT - static_cast<int>( levelMap.size() ))/ 2;
}



void GraphicOutputManager::update(std::vector<std::shared_ptr<DataUpdate>> data)
{
	// Clear the current renderer.
	SDL_RenderClear(renderer);

	// Draw the walls.
	drawBackground(levelMap);

	// Update the map based on the incoming data

	for (std::shared_ptr<DataUpdate> &dataPtr : data) {

		// Look up in the ID in the sprite map
		auto mapPair = spriteObjects.find(dataPtr->getID());

		if (mapPair == spriteObjects.end())
			std::cout << "Element not found" << '\n';
		else {
			// Look at ObjectType specific data
			std::vector <std::string> tempConstructorData;
			switch (dataPtr->getObjectType()) {
			case DataUpdate::ObjectType::PLAYER:
				tempConstructorData = DataToolkit::getSubs(dataPtr->getData(), ',');
				this->lives = stoi(tempConstructorData[0]);

				spriteManager->moveSprite(mapPair->second, dataPtr->getObjectXPosition(), dataPtr->getObjectYPosition(),
					static_cast<CharacterOrientation>(stoi(tempConstructorData[1]))); // turn integer into enum
				break;
			default:
				if (dataPtr->getAction() == DataUpdate::Action::ELIMINATE) {
					spriteObjects.erase(mapPair);
				}
				else {
					spriteManager->moveSprite(mapPair->second, dataPtr->getObjectXPosition(), dataPtr->getObjectYPosition());
				}
				break;
			}

		}

	}

	// Loop through all the objects and draw them.
	for (auto &mapPair : this->spriteObjects) {
		int x = mapPair.second->getXPosition();
		int y = mapPair.second->getYPosition();

		SDL_Rect dst = { (x+ xOffset) * TILESIZE , (y+yOffset) * TILESIZE, TILESIZE,
			TILESIZE };
		SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(mapPair.second),
			&dst);
	}

	// Draw the lives.
	drawLives();

	// Update the screen.
	SDL_RenderPresent(renderer);
}

void GraphicOutputManager::update(UserInputType userInput)
{
	// Purely for testing
	
	// Clear the current renderer.
	SDL_RenderClear(renderer);

	// Draw the walls.
	drawBackground(levelMap);
	
	// Look up in the ID in the sprite map
	auto mapPair = spriteObjects.find("001");

	if (mapPair == spriteObjects.end())
		std::cout << "Element not found" << '\n';
	else {
		spriteManager->moveSprite(mapPair->second, userInput);
	}

	// Loop through all the objects and draw them.
	for (auto &mapPair : this->spriteObjects) {
		int x = mapPair.second->getXPosition();
		int y = mapPair.second->getYPosition();

		SDL_Rect dst = { (x + xOffset) * TILESIZE + xOffset, (y+ yOffset) * TILESIZE , TILESIZE,
						TILESIZE };
		SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(mapPair.second),
			&dst);
	}
	

	// Update the screen.
	SDL_RenderPresent(renderer);
}

void GraphicOutputManager::drawBitmap(SDL_Texture* texture) {
	using namespace SpriteAttributes;
	SDL_Rect dst = { 0, 0 , (SCREEN_WIDTH+1)*TILESIZE, (SCREEN_HEIGHT+1)*TILESIZE };
	
	// Clear the current renderer.
	SDL_RenderClear(renderer);

	SDL_RenderCopy(renderer, texture, NULL, &dst);//NULL to show the entire structure

	// Update the screen.
	SDL_RenderPresent(renderer);
}

void GraphicOutputManager::showGameOverScreen() {
	drawBitmap(gameOverScreen);
}

void GraphicOutputManager::showVictoryScreen() {
	drawBitmap(victoryScreen);
}



/// Initialises the UI::window and the UI::renderer.
void GraphicOutputManager::init()
{
	// Init SDL
	SDL_Init(SDL_INIT_EVERYTHING);

	// Create a Window in the middle of the screen
	window = SDL_CreateWindow("The Awesome Game", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH * TILESIZE,
		SCREEN_HEIGHT* TILESIZE, SDL_WINDOW_SHOWN);

	// Create a new renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
		SDL_RENDERER_PRESENTVSYNC);
}

/// From the Pacman Code
void GraphicOutputManager::loadTextures()
{
	// Load sprite sheet
	//sheet = this->loadTexture("resources/sam_gfx.bmp");
	spriteManager->setSheet(this->loadTexture("resources/sam_gfx.bmp"));
	//seperateTiles(); //moved to SpriteManager

	// Load game over screen
	gameOverScreen = this->loadTexture("resources/GAME_OVER.bmp");
	victoryScreen = this->loadTexture("resources/set1_victory.bmp");
}



/// From the Pacman Code
void GraphicOutputManager::drawBackground(std::vector<std::vector<int>> &map)
{
	using namespace SpriteAttributes;
	// Draw a wall on each position containing a one
	for (size_t i = 0; i < map.size(); i++) {
		for (size_t j = 0; j < map[i].size(); j++) {
			SDL_Rect dst = { (static_cast<int>(j) + xOffset )* TILESIZE,
				             (static_cast<int>(i) + yOffset) * TILESIZE , TILESIZE,
				TILESIZE };
			if (map[i][j] == 1) {
				//SDL_RenderCopy(renderer, sheet, &tileSet[WALL][DOWN], &dst);
				SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(WALL, CharacterOrientation::Down), &dst);
				//SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(WALL,DOWN), &dst);
			}
			else if (map[i][j] == 2) {
				//SDL_RenderCopy(renderer, sheet, &tileSet[KEY][DOWN], &dst);
				SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(KEY, CharacterOrientation::Down), &dst);
			}
		}
	}
}

/// Draws an amount of pacmans corresponding to the amount of lives
// From the Pacman Code
void GraphicOutputManager::drawLives()
{
	using namespace SpriteAttributes;
	for (int i = 0; i < lives; i++) {
		SDL_Rect dst = { SCREEN_HEIGHT * TILESIZE - i * TILESIZE, (SCREEN_HEIGHT -1) * TILESIZE, TILESIZE,
						TILESIZE };
		//SDL_RenderCopy(renderer, sheet, &tileSet[PACMAN][LEFT], &dst);
		SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(PACMAN, CharacterOrientation::Left), &dst);
	}
}

// From the Pacman Code
SDL_Texture *GraphicOutputManager::loadTexture(const std::string &file)
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



