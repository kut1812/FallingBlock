#include "Shield.h"
#include "../Character/Player.h"
bool ShieldSkill::init() {
	this->skillCooldown = 0.0f;
	this->effectiveTime = 5.0f;
	this->maxSkillCooldown = 10.0f;
	if (Director::getInstance()->getRunningScene())
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		skillSprite = Sprite::create("control/fb_ctrl_skill_sheild_wait.png");
		skillSprite->setPosition(Vec2(visibleSize.width * 0.79, visibleSize.height * 0.27));
		Director::getInstance()->getRunningScene()->addChild(skillSprite, 3);
	}
	return true;
}

void ShieldSkill::use() {
	if (this->skillCooldown < 0) {
		_player->setInvincible(true);
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
			}, this, effectiveTime, effectiveTime, effectiveTime, false, "reset_shield_skill");
		this->skillCooldown = maxSkillCooldown;
	}
}
ShieldSkill::~ShieldSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_shield_skill", this);
}