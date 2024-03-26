#ifndef __COIN_H__
#define __COIN_H__

#include "cocos2d.h"
#include "Utilities/Utilities.h"

USING_NS_CC;
class Coin : public Sprite
{
public:
	static Coin* create();
	virtual bool init();
	void setCoinDouble();
	void setCoinNormal();
	bool addPhysics();
	PhysicsBody* getPhysicsBody() { return physics; }
	bool isDouble() const { return isDoub; };
private:
	PhysicsBody* physics;
	bool isDoub = false;
};

#endif // !__COIN_H__