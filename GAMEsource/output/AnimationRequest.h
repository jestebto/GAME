#ifndef ANIMATION_REQUEST_H
#define ANIMATION_REQUEST_H

#include "AnimationFrame.h"
#include "GameSprite.h"

///Used to store elements associated with an animation, to pass around
/**
* Namely, a GameSprite element, an artType and an action.
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
	GameSprite* elementRef; ///< the game sprite that should be animated
	SpriteAttributes::ArtType art; ///< the art type to use when animating that sprite e.g. PACMAN, BLINKY
	SpriteAttributes::AnimationTypes action; ///< the action that describes the animations e.g. ATTACK, GET_HIT, DEATH etc
};

#endif /* ANIMATION_REQUEST_H */