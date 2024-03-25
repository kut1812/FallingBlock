#include "Shield.h"
#include "../Character/Player.h"
bool ShieldSkill::init() {


	return true;
}

void ShieldSkill::use() {
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
		}, this, 5.0, 5.0, 5.0, false, "reset_shield_skill");
}
ShieldSkill::~ShieldSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_shield_skill", this);
}