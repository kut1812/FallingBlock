#include "MoveLeftState.h"
#include "../Character/Player.h"
void MoveLeftState::enter() {
	if (player) {
		player->getSprite()->runAction(RepeatForever::create(Animate::create(AnimationCache::getInstance()->getAnimation("MOVE_ANIM"))));
		player->getSprite()->setFlippedX(true);
		player->getWingSprite()->setFlippedX(true);
		player->getWingSprite()->setPosition(Vec2(player->getSprite()->getPositionX() + player->getSprite()->getContentSize().width + 20, player->getSprite()->getPositionY() + 20));
	}
}

void MoveLeftState::exit() {
	if (player->getSprite()->getNumberOfRunningActions() > 0)
	{
		player->getSprite()->stopAllActions();
	}
}

void MoveLeftState::update(float dt) {

}