#include "X2Coin.h"

bool X2CoinSkill::init() {


	return true;
}

void X2CoinSkill::use() {
	_player->setX2Coin(true);
}