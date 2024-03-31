#include "X2Jump.h"
#include "../Character/Player.h"
bool X2JumpSkill::init() {
	if (!Node::init()) return false;
	this->skillCooldown = 0.0f;
	this->effectiveTime = 5.0f;
	this->maxSkillCooldown = 10.0f;
	if (Director::getInstance()->getRunningScene())
	{

		auto visibleSize = Director::getInstance()->getVisibleSize();
		skillSprite = Sprite::create("control/fb_ctrl_skill_dup_jump_wait.png");
		skillSprite->setPosition(Vec2(visibleSize.width * 0.85, visibleSize.height * 0.32));
		skillSprite->retain();
		Director::getInstance()->getRunningScene()->addChild(skillSprite, 3);
	}

	return true;
}


void X2JumpSkill::use() {
	CCLOG("%f this->skillCooldown", this->skillCooldown); // output: -431602080.000000
	if (this->skillCooldown <= 0) {
		auto label = Label::createWithTTF(StringUtils::format("%.1f", this->maxSkillCooldown), "font/Baloo2/Baloo2-Bold.ttf", 24);
		Director::getInstance()->getRunningScene()->addChild(label, 3);

		float remainingCooldown = this->maxSkillCooldown;
		Director::getInstance()->getScheduler()->schedule([=](float dt) mutable {
			remainingCooldown -= dt;
			label->setString(StringUtils::format("%.1f", remainingCooldown));

			if (remainingCooldown <= 0) {
				// Xóa label khi cooldown <= 0
				label->removeFromParent();
				this->skillCooldown = this->maxSkillCooldown; // Reset cooldown
			}
			}, label, 0.1f, kRepeatForever, 0.0f, false, "cooldown_scheduler3");

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