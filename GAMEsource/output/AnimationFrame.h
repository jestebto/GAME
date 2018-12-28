#pragma once

#ifndef ANIMATION_FRAME_H
#define ANIMATION_FRAME_H

#include <vector>
#include "GameSprite.h"

/// Define terms used for animations

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

	SpriteAttributes::ArtType art;
	SpriteAttributes::Description description;
	int movement;

};

#endif // ANIMATION_FRAME_H
