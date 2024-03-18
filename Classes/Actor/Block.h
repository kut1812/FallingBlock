#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"

USING_NS_CC;
class Block : public Sprite
{
public:
	static Block* create(std::string tyleBlock);
	virtual bool init(std::string tyleBlock);

	bool addPhysics();
	PhysicsBody* getPhysicsBody() { return physics; }
private:
	PhysicsBody* physics;
};

#endif // !__BLOCK_H__
