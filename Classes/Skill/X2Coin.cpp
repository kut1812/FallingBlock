#include "X2Coin.h"
#include "../Character/Player.h"

bool X2CoinSkill::init() {
	this->skillCooldown = 0.0f;
	this->effectiveTime = 8.0f;
	this->maxSkillCooldown = 20.0f;
	if (Director::getInstance()->getRunningScene())
	{
		auto visibleSize = Director::getInstance()->getVisibleSize();
		skillSprite = Sprite::create("control/fb_ctrl_skill_dup_coin_wait.png");
		skillSprite->setPosition(Vec2(visibleSize.width * 0.77, visibleSize.height * 0.15));
		Director::getInstance()->getRunningScene()->addChild(skillSprite, 3);
	}
	return true;
}

void X2CoinSkill::use() {
	if (this->skillCooldown < 0) {

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
			}, label, 0.1f, kRepeatForever, 0.0f, false, "cooldown_scheduler1");


		_player->setX2Coin(true);
		Director::getInstance()->getScheduler()->schedule([this](float dt) {
			_player->setX2Coin(false);
			}, this, this->effectiveTime, this->effectiveTime, this->effectiveTime, false, "reset_x2_coin");
		this->skillCooldown = this->maxSkillCooldown;
	}
}

X2CoinSkill::~X2CoinSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_x2_coin", this);
}