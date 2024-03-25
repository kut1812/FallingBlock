#include "X2Coin.h"
#include "../Character/Player.h"

bool X2CoinSkill::init() {


	return true;
}

void X2CoinSkill::use() {
	_player->setX2Coin(true);
	Director::getInstance()->getScheduler()->schedule([this](float dt) {
		_player->setX2Coin(false);
		}, this, 5.0, 5.0, 5.0, false, "reset_x2_coin");
}

X2CoinSkill::~X2CoinSkill() {
	Director::getInstance()->getScheduler()->unschedule("reset_x2_coin", this);
}