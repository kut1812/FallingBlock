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
	CCLOG("%f this->skillCooldown", this->skillCooldown); // output: -431602080.000000
	if (this->skillCooldown <= 0) {
		_player->setMaxJumpCount(2);
		_player->getWingSprite()->setVisible(true);
		Director::getInstance()->getScheduler()->schedule([this](float dt) {
			_player->setMaxJumpCount(1);
			if(_player->getWingSprite())
				_player->getWingSprite()->setVisible(false);
			}, this, effectiveTime, effectiveTime, effectiveTime, false, "reset_max_jump_count");
		this->skillCooldown = maxSkillCooldown;
	}
}

X2JumpSkill::~X2JumpSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_max_jump_count", this);
}