#include "X2Coin.h"
#include "../Character/Player.h"

bool X2CoinSkill::init() {
	this->skillCooldown = 0.0f;
	this->effectiveTime = 8.0f;
	return true;
}

bool X2CoinSkill::use() {
	if (this->skillCooldown <= 0 && _player) {
		_player->setX2Coin(true);
		Director::getInstance()->getScheduler()->schedule([this](float dt) {
			if(_player)
				_player->setX2Coin(false);
			}, this, this->effectiveTime, 0.0f, 0.0f, false, "reset_x2_coin");
		this->skillCooldown = this->maxSkillCooldown;
		return true;
	}
	return false;
}

X2CoinSkill::~X2CoinSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_x2_coin", this);
}