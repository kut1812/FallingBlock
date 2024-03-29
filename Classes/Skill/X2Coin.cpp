#include "X2Coin.h"
#include "../Character/Player.h"

bool X2CoinSkill::init() {
	this->skillCooldown = 10.0f;
	return true;
}

void X2CoinSkill::use() {
	if (this->skillCooldown < 0) {
		_player->setX2Coin(true);
		Director::getInstance()->getScheduler()->schedule([this](float dt) {
			_player->setX2Coin(false);
			}, this, this->skillCooldown, this->skillCooldown, this->skillCooldown, false, "reset_x2_coin");
		this->skillCooldown = 10.0f;
	}
}

X2CoinSkill::~X2CoinSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_x2_coin", this);
}