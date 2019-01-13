#ifndef ANIMATION_REQUEST_H
#define ANIMATION_REQUEST_H

#include "AnimationFrame.h"
#include "GameSprite.h"

/**
* Used to store elements associated with an animation. Namely, a GameSprite element, an artType and an action.
* This makes passing "animations" around easier.
*/
class AnimationRequest
{
public:
	AnimationRequest(GameSprite *element, SpriteAttributes::ArtType artType, SpriteAttributes::AnimationTypes animationAction) {
		this->elementRef = element;
		this->art = artType;
		this->action = animationAction;
	};
	~AnimationRequest() {};

public:
	GameSprite* elementRef;
	SpriteAttributes::ArtType art;
	SpriteAttributes::AnimationTypes action;
};

#endif /* ANIMATION_REQUEST_H */