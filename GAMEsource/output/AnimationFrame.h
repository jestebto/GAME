#pragma once
//Lior: TODO: remove, currently not use
#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "GameSprite.h"

/// Define terms used for animations

namespace AnimationTerms {
	enum AnimationTypes {
		NOTHING, IDLE, ATTACK, DIE, LOOK_LEFT, LOOK_RIGHT, WALK
	};

}

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

#endif // ANIMATION_H
