#include "IdleState.h"
#include "../Character/Player.h"
void IdleState::enter() {
	if (player) {
		player->getSprite()->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("IDLE_ANIM"))));
	}
}

void IdleState::exit() {
	if (player->getSprite()->getNumberOfRunningActions() > 0)
	{
		player->getSprite()->stopAllActions();
	}

	if (player->getSprite()->getNumberOfRunningActions() > 0) player->getSprite()->stopAllActions();
}

void IdleState::update(float dt) {

}