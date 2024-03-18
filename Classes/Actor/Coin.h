#ifndef __COIN_H__
#define __COIN_H__

#include "cocos2d.h"

USING_NS_CC;
class Coin : public Sprite
{
public:
	static Coin* create();
	virtual bool init();

	bool addPhysics();
	PhysicsBody* getPhysicsBody() { return physics; }
private:
	PhysicsBody* physics;
};

#endif // !__COIN_H__
