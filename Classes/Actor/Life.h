#ifndef __LIFE__
#define __LIFE__

#include "cocos2d.h"
#include "Utilities/Utilities.h"

USING_NS_CC;
class Life : public Sprite
{
public:
	static Life* create();
	virtual bool init();
	bool addPhysics();
	PhysicsBody* getPhysicsBody() { return physics; }
private:
	PhysicsBody* physics;
};

#endif // !__LIFE__