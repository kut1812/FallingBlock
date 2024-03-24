#include "X2Jump.h"
#include "../Character/Player.h"
bool X2JumpSkill::init() {
	this->effectiveTime = 5.0f;
	return true;
}


void X2JumpSkill::use() {
	_player->setMaxJumpCount(2);
	_player->getWingSprite()->setVisible(true);
	Director::getInstance()->getScheduler()->schedule([this](float dt) {
		_player->setMaxJumpCount(1);
		_player->getWingSprite()->setVisible(false);
		}, this, 5.0, 5.0, 5.0, false, "reset_max_jump_count");

}