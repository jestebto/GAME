/*
 *  Created on: 28 November, 2018
 *      Author: Lior Sinai
 * Description: See GraphicInterface.h
 */

#include "GraphicOutputManager.h"

GraphicOutputManager::GraphicOutputManager()
{
	// Initialize window and load textures.
	this->init();
	//All other setup is done in GrahpicInterface::loadlevel once data has been received

	// Load game over screen
	spriteManager = std::make_unique<TileManager>(this->loadTexture("resources/sam_gfx.bmp"));
	gameOverScreen = this->loadTexture("resources/GAME_OVER.bmp");
	victoryScreen = this->loadTexture("resources/set1_victory.bmp");
	genericErrorScreen = this->loadTexture("resources/ERROR.bmp");
}


GraphicOutputManager::~GraphicOutputManager()
{
	SDL_DestroyTexture(gameOverScreen);
	SDL_DestroyTexture(victoryScreen);
	SDL_DestroyTexture(genericErrorScreen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void GraphicOutputManager::loadLevel(OutputData inputString) {
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

		if (objectType >= 0 && objectType <= 3) // these are the symbols used as keys
		{
			// erase the part of the string that contains the object type and the ampersand symbol
			objectVector[i].erase(0, amp + 1);
		}

		switch (objectType) {
		case 0: { // 0 is map
			setBackground(objectVector[i]);
			break;
		}
		case 1: { //1 is player
			//separate the data to construct the new object
			tempConstructorData = DataToolkit::getSubs(objectVector[i],',');

			// tempConstructorData format: {"ID, x, y, lives"} 
			this->spriteObjects[tempConstructorData[0]] = std::make_unique<CharSprite> (stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), PACMAN, SpriteAttributes::UP, CharacterOrientation::Up);
			this->lives= stoi(tempConstructorData[3]);

			tempConstructorData = {}; //make sure the vector is empty in the next case <TO DO> make sure if this is needed
			break;
		}
		case 2: { // 2 is an enemy
			// separate the data to construct the new object
			// Data format: "ID,x,y,lives,"
			tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');
			// create a new enemy storing a shared pointer to it
			this->spriteObjects[tempConstructorData[0]] = std::make_unique<GameSprite>( stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), SCAREDINV, SpriteAttributes::DEFAULT);

			tempConstructorData = {}; // make sure the vector is empty in the next case
			break;
		}
		case 3: { // 3 is a power up
			// separate the data to construct the new object
			// Data format: "ID,x,y,livesBonus,"
			tempConstructorData = DataToolkit::getSubs(objectVector[i], ',');
			this->spriteObjects[tempConstructorData[0]] = std::make_unique<GameSprite>(stoi(tempConstructorData[1]),
				stoi(tempConstructorData[2]), APPLE, SpriteAttributes::DEFAULT);
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
	// Update the map based on the incoming data
	// Note: animations will be called and will be played on the old renderer
	for (std::shared_ptr<DataUpdate> &dataPtr : data) {

		// Look up in the ID in the sprite map
		auto mapPair = spriteObjects.find(dataPtr->getID());

		if (mapPair == spriteObjects.end())
			std::cout << "Element not found" << '\n';
		else {
			// Look at ObjectType specific data
			std::vector <std::string> tempConstructorData;

			DataUpdate::ObjectType type = dataPtr->getObjectType();
			DataUpdate::Action action =  dataPtr->getAction();
			switch (type) {
			case DataUpdate::ObjectType::PLAYER: {
				// Data = "lives, (int)CharacterOrientation"
				tempConstructorData = DataToolkit::getSubs(dataPtr->getData(), ',');

				this->lives = stoi(tempConstructorData[0]);

				switch (action) {
				case DataUpdate::Action::ATTACK: {
					playAnimation(mapPair->second, SpriteAttributes::PACMAN, AnimationTerms::AnimationTypes::ATTACK);
					break;
				}
				default: { //Assume it is a movement
					(mapPair->second)->setOrientation(static_cast<CharacterOrientation>(stoi(tempConstructorData[1])));
					(mapPair->second)->moveSprite(dataPtr->getObjectXPosition(), dataPtr->getObjectYPosition()); //Calls the CharSprite code
					break;
				}
				}
			} break;
			case DataUpdate::ObjectType::ENEMY: {

				switch (action) {
				case DataUpdate::Action::ELIMINATE: {
					playAnimation(mapPair->second, SpriteAttributes::SCARED, AnimationTerms::AnimationTypes::DIE);
					spriteObjects.erase(mapPair); // since the map owns a unique_ptr, this calls the destructor as well.
					break;
				}
				default: { //Assume it is a movement
					(mapPair->second)->moveSprite(dataPtr->getObjectXPosition(), dataPtr->getObjectYPosition()); 
					break;
				}
				}
			} break;
			default:
				switch (action) {
				case DataUpdate::Action::ELIMINATE: {
						spriteObjects.erase(mapPair); // since the map owns a unique_ptr, this calls the destructor as well.
						break;
				}
				default: { //Assume it is a movement
						(mapPair->second)->moveSprite(dataPtr->getObjectXPosition(), dataPtr->getObjectYPosition());
						break;
				}
				}
			}

		}

	}

	// Clear the current renderer.
	SDL_RenderClear(renderer);

	// Draw the walls.
	drawBackground(levelMap);

	// Loop through all the objects and draw them.
	for (auto &mapPair : this->spriteObjects) {
		int x = mapPair.second->getXPosition();
		int y = mapPair.second->getYPosition();

		SDL_Rect dst = { (x + xOffset) * TILESIZE , (y + yOffset) * TILESIZE, TILESIZE,
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
	
	// Look up in the ID in the sprite map
	auto mapPair = spriteObjects.find("001");

	if (mapPair == spriteObjects.end())
		std::cout << "Element not found" << '\n';
	else {
		(mapPair->second)->moveSprite(userInput);

		if (userInput == UserInputType::Hit) {
			playAnimation(mapPair->second, SpriteAttributes::PACMAN, AnimationTerms::AnimationTypes::ATTACK);
		}
	}

	// Clear the current renderer.
	SDL_RenderClear(renderer);

	// Draw the walls.
	drawBackground(levelMap);

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

void GraphicOutputManager::playAnimation(std::unique_ptr<GameSprite> const& element, SpriteAttributes::ArtType type, AnimationTerms::AnimationTypes action)
{
	try {
		std::vector<AnimationFrame>* animationFrames = spriteManager->getAnimationFrames(element, type, action);


		int x = element->getXPosition();
		int y = element->getYPosition();
		SDL_Rect dst = { (x + xOffset) * TILESIZE + xOffset, (y + yOffset) * TILESIZE , TILESIZE,
				TILESIZE };
		SDL_RenderFillRect(renderer, &dst); //fill the current spot with a blank rectangle

		for (AnimationFrame frame : *animationFrames) {
			if (frame.movement != 0) {
				SDL_RenderFillRect(renderer, &dst); //fill the current spot with a blank rectangle
				element->moveSprite(frame.movement);
				int x = element->getXPosition();
				int y = element->getYPosition(); 
				dst = { (x + xOffset) * TILESIZE + xOffset, (y + yOffset) * TILESIZE , TILESIZE,
		TILESIZE };
			}
			

			SDL_RenderFillRect(renderer, &dst); //fill the current spot with a blank rectangle
			SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(frame.art, frame.description),
				&dst);

			SDL_RenderPresent(renderer);
			std::this_thread::sleep_for(std::chrono::milliseconds(100));

		}
	}
	catch (std::out_of_range) // Animation does not exist in any of the animation maps
	{
		throw std::out_of_range("Animation does not exist"); //TO DO: if you catch it and throw a different thing, do we need a custom exception in this case?
	}
}

void GraphicOutputManager::drawBitmap(SDL_Texture* texture) {
	using namespace SpriteAttributes;
	SDL_Rect dst = { 0, 0 , (SCREEN_WIDTH)*TILESIZE, (SCREEN_HEIGHT-1)*TILESIZE };
	
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

void GraphicOutputManager::showGenericErrorScreen() {
	drawBitmap(genericErrorScreen);
}



// Initialises the UI::window and the UI::renderer.
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


// From the Pacman Code
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
				SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(WALL, SpriteAttributes::DEFAULT), &dst);
			}
			else if (map[i][j] == 2) {
				SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(KEY, SpriteAttributes::DEFAULT), &dst);
			}
		}
	}
}

/// Draws an amount of pacmans corresponding to the amount of lives
// From the Pacman Code
void GraphicOutputManager::drawLives()
{
	using namespace SpriteAttributes;
	for (int i = 0; i < this->lives; i++) {
		SDL_Rect dst = { SCREEN_HEIGHT * TILESIZE - i * TILESIZE, (SCREEN_HEIGHT -1) * TILESIZE, TILESIZE,
						TILESIZE };
		SDL_RenderCopy(renderer, spriteManager->getSheet(), spriteManager->getTile(PACMAN, SpriteAttributes::LEFT), &dst);
	}
}

// From the Pacman Code
SDL_Texture *GraphicOutputManager::loadTexture(const std::string &file)
{
	SDL_Surface *surf = SDL_LoadBMP(file.c_str());
	if (surf == nullptr) {
		std::string errorMsg= "Error while loading texture bitmap: ";
		errorMsg = errorMsg + SDL_GetError();
		throw errorMsg;
		//std::cerr << "Error while loading texture bitmap: " << SDL_GetError() << std::endl;
	}
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surf);
	if (texture == nullptr) {
		std::string errorMsg = "Error while loading texture bitmap: ";
		errorMsg = errorMsg + SDL_GetError();
		throw errorMsg;
		//std::cerr << "Error while creating texture: " << SDL_GetError() << std::endl;
	}
	SDL_FreeSurface(surf);
	return texture;
}



