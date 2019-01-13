#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H

#include <vector>
#include "GameSprite.h"

/**
* Each animation frame consists of a single sprite artwork, which can be uniquely identified 
* by an artType and a description e.g. PACMAN UP.
* Can also encode extra information in the frame, such as how to move the sprite during the 
* animation
*/
class AnimationFrame
{
public:
	AnimationFrame(SpriteAttributes::ArtType artType, SpriteAttributes::Description des,int value) {
		this->art = artType;
		this->description = des;
		this->movement = value;
	}
	;
	~AnimationFrame() {};
	
	/// An artwork type and an artwork description uniquely defines an animation frame
	//typedef std::pair<SpriteAttributes::ArtType, SpriteAttributes::Description> AnimationFrame;

	SpriteAttributes::ArtType art; ///< An artwork type to identify the sprite
	SpriteAttributes::Description description; ///< further description to identify the sprite
	int movement; ///< Can encode a movement if desired. Set to 0 for no movement.

};

#endif // ANIMATION_FRAME_H
