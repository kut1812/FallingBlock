#include "IdleState.h"
#include "../Character/Player.h"
void IdleState::enter() {
		player->getSprite()->runAction(RepeatForever::create(player->idleAnimation));
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