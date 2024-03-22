#include "MoveLeftState.h"
#include "../Character/Player.h"
void MoveLeftState::enter() {
	if (player) {
		player->getSprite()->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("MOVE_ANIM"))));
		player->getSprite()->setFlippedX(true);
	}
}

void MoveLeftState::exit() {
	if (player->getSprite()->getNumberOfRunningActions() > 0)
	{
		player->getSprite()->stopAllActions();
		player->getSprite()->setFlippedX(false);
	}
}

void MoveLeftState::update(float dt) {

}