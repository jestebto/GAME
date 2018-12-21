#pragma once
//Lior: TODO: remove, currently not use
#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "GameSprite.h"

/// Define terms used for animations
namespace AnimationTerms
{
	/// An artwork type and an artwork description uniquely defines an animation frame
	typedef std::pair<SpriteAttributes::ArtType, SpriteAttributes::Description> AnimationFrame;

	/// Different kinds of animations that be can called
	enum AnimationTypes {
		NOTHING, IDLE, ATTACK, DIE,  LOOK_LEFT, LOOK_RIGHT, WALK
	};
};

#endif // ANIMATION_H
