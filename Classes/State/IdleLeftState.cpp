#include "IdleLeftState.h"
#include "../Character/Player.h"
void IdleLeftState::enter() {
	if (player) {
		player->getSprite()->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("IDLE_ANIM"))));
	}
}

void IdleLeftState::exit() {
	if (player->getSprite()->getNumberOfRunningActions() > 0)
	{
		player->getSprite()->stopAllActions();
	}

}

void IdleLeftState::update(float dt) {

}