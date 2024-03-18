#ifndef __COIN_MANAGER_H__
#define __COIN_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class CoinManager
{
public:
	static CoinManager* getInstance();

	void increaseCoins(int coins) { _amount += coins; }
	void decreaseCoins(int coins) {_amount -= coins; }
	int getCoin(){return _amount;}
private:
	static CoinManager* _instance;

	int _amount;
};

#endif // !__COIN_MANAGER_H__