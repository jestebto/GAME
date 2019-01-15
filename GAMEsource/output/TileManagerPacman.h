#ifndef TILEMANAGERPACMAN_H
#define TILEMANAGERPACMAN_H

#include "TileManager.h"
#include <memory>
/// A tile manager specifically for the Pacman tiles
class TileManagerPacman :
	public TileManager
{
public:
	TileManagerPacman(SDL_Texture*);
	~TileManagerPacman();

	/// getTile for a unique Sprite. If not found, return a random tile
	SDL_Rect* getTile(std::unique_ptr<GameSprite> const&);
	/// getTile for general printing e.g. for the background. If not found, return a random tile
	SDL_Rect* getTile(SpriteAttributes::ArtType, SpriteAttributes::Description);

	/// Get a vector of animation frames. Search through different private map<>animations
	virtual std::vector<AnimationFrame>* getAnimationFrames(GameSprite*, SpriteAttributes::ArtType, SpriteAttributes::AnimationTypes);

	const int tileSize = 24; ///< tile size for each Sprite. Does not have to be the same as the graphic output manager tile size (but it's better if it is)
//enum { PACMAN_TILESIZE = 24 }; 
private:
	/// Seperate tiles into a tileSet map. Usage is:
	/// tileSet[<ArtType>][<Description>]
	/// and the tile set itself is in GraphicInterface::sheet
	void createTileMap(); //Note: this was the old separateTiles(). New name to show that it doesn't actually seperate them; it only creates an index of where each sprite is in the bigger picture
	void createAnimationSequences(); ///< create a list of connected sprites and descriptions to use in an animation sequence
	
	/// Hard code the animation sequences
	/// For the player, use a map with the key as the orientation and the action
	/// For the other objects, the orientation is not important, so use the key as object type and the action
	/// An art type and a description uniquely defines an animation frame
	std::map <CharacterOrientation, std::map<SpriteAttributes::AnimationTypes, std::vector<AnimationFrame>>> animationsPacman;
	std::map <SpriteAttributes::ArtType, std::map<SpriteAttributes::AnimationTypes, std::vector<AnimationFrame>>> animationsOther;

};

#endif /* TILEMANAGERPACMAN_H */
