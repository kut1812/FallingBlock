#include "MoveLeftState.h"
#include "../Character/Player.h"
void MoveLeftState::enter() {
		player->getSprite()->runAction(RepeatForever::create(player->walkAnimation));
		player->getSprite()->setFlippedX(true);
		player->getWingSprite()->setFlippedX(true);
		player->getWingSprite()->setPosition(Vec2(player->getSprite()->getContentSize().width, player->getSprite()->getContentSize().height * 0.9));
}

void MoveLeftState::exit() {
	if (player->getSprite()->getNumberOfRunningActions() > 0)
	{
		player->getSprite()->stopAllActions();
	}
}

void MoveLeftState::update(float dt) {

}