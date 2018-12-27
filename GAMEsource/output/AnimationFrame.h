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
	AnimationFrame(SpriteAttributes::ArtType artType, SpriteAttributes::Description des) {
		this->art = artType;
		this->description = des;
	}
	;
	~AnimationFrame() {};
	
	/// An artwork type and an artwork description uniquely defines an animation frame
	//typedef std::pair<SpriteAttributes::ArtType, SpriteAttributes::Description> AnimationFrame;

	SpriteAttributes::ArtType art;
	SpriteAttributes::Description description;

};

#endif // ANIMATION_H
