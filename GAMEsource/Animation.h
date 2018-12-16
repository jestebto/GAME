#pragma once
//Lior: TODO: remove, currently not use
#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>
#include "GameSprite.h"

namespace AnimationTerms
{
	/// An art type and a description uniquely defines an animation frame
	typedef std::pair<SpriteAttributes::ArtType, SpriteAttributes::Description> AnimationFrame;

	enum AnimationTypes {
		NOTHING, IDLE, ATTACK, DIE,  LOOK_LEFT
	};
};

#endif // ANIMATION_H
