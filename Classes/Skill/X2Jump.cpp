#include "X2Jump.h"
#include "../Character/Player.h"
bool X2JumpSkill::init() {
	this->skillCooldown = 0.0f;
	this->effectiveTime = 3.0f;
	return true;
}


bool X2JumpSkill::use() {
	CCLOG("%f this->maxSkillCooldown 2", this->maxSkillCooldown);
	if (this->skillCooldown <= 0 && _player) {
		_player->setMaxJumpCount(2);
		_player->getWingSprite()->setVisible(true);
		Director::getInstance()->getScheduler()->schedule([this](float dt) {
			_player->setMaxJumpCount(1);
			if(_player->getWingSprite())
				_player->getWingSprite()->setVisible(false);
			}, this, this->effectiveTime, 0.0f, 0.0f, false, "reset_max_jump_count");
		CCLOG("%f this->maxSkillCooldown 3", this->maxSkillCooldown);
		this->skillCooldown = maxSkillCooldown;
		return true;
	}
	return false;
}

X2JumpSkill::~X2JumpSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_max_jump_count", this);
}