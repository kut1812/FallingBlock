#include "X2Jump.h"
#include "../Character/Player.h"
bool X2JumpSkill::init() {
	if (!Node::init()) return false;
	this->skillCooldown = 0.0f;
	this->effectiveTime = 5.0f;
	this->maxSkillCooldown = 10.0f;
	return true;
}


void X2JumpSkill::use() {
	if (this->skillCooldown <= 0 && _player) {
		_player->setMaxJumpCount(2);
		_player->getWingSprite()->setVisible(true);
		Director::getInstance()->getScheduler()->schedule([this](float dt) {
			_player->setMaxJumpCount(1);
			if(_player->getWingSprite())
				_player->getWingSprite()->setVisible(false);
			}, this, this->effectiveTime, 0.0f, 0.0f, false, "reset_max_jump_count");
		this->skillCooldown = maxSkillCooldown;
	}
}

X2JumpSkill::~X2JumpSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_max_jump_count", this);
}