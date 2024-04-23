#include "IdleLeftState.h"
#include "../Character/Player.h"
void IdleLeftState::enter() {
		player->getSprite()->runAction(RepeatForever::create(player->idleAnimation));
}

void IdleLeftState::exit() {
	if (player->getSprite()->getNumberOfRunningActions() > 0)
	{
		player->getSprite()->stopAllActions();
	}

}

void IdleLeftState::update(float dt) {

}