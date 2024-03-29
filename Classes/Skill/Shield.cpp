#include "Shield.h"
#include "../Character/Player.h"
bool ShieldSkill::init() {
	this->skillCooldown = 10.0f;
	return true;
}

void ShieldSkill::use() {
	if (this->skillCooldown < 0) {
		_player->setInvincible(true);
		_player->getShieldSprite()->setVisible(true);
		auto shieldBody = PhysicsBody::createBox(_player->getShieldSprite()->getContentSize() - Size(50, 50), PhysicsMaterial(1.0f, 0.1f, 1.0f));
		shieldBody->setDynamic(false);
		shieldBody->setCollisionBitmask(80);
		shieldBody->setContactTestBitmask(true);
		shieldBody->setMass(0.1);
		shieldBody->setTag(54);
		_player->getShieldSprite()->addComponent(shieldBody);
		Director::getInstance()->getScheduler()->schedule([this, shieldBody](float dt) {
			_player->setInvincible(false);
			if (_player->getShieldSprite()) {
				_player->getShieldSprite()->setVisible(false);
				_player->getShieldSprite()->removeComponent(shieldBody);
			}
			}, this, this->skillCooldown, this->skillCooldown, this->skillCooldown, false, "reset_shield_skill");
		this->skillCooldown = 10;
	}
}
ShieldSkill::~ShieldSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_shield_skill", this);
}