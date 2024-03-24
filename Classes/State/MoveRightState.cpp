#include "MoveRightState.h"
#include "../Character/Player.h"
void MoveRightState::enter() {
	if (player) {
		player->getSprite()->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("MOVE_ANIM"))));
		player->getSprite()->setFlippedX(false);
		player->getWingSprite()->setFlippedX(false);
		player->getWingSprite()->setPosition(Vec2(0, player->getSprite()->getContentSize().height * 0.9));
	}
}

void MoveRightState::exit() {
	if (player->getSprite()->getNumberOfRunningActions() > 0)
	{
		player->getSprite()->stopAllActions();
	}
}

void MoveRightState::update(float dt) {

}