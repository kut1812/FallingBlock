#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"

USING_NS_CC;
class Block : public Sprite
{
public:
	static Block* create(std::string tyleBlock);
	virtual bool init(std::string tyleBlock);
	void setFlop();
	bool addPhysics();
	PhysicsBody* getPhysicsBody() { return blockBody; };
	Size getSpriteSize() const { return this->getContentSize(); };
	void setStatus(std::string stt) { status = stt; };
	std::string getStatus() const { return status; };
	void setBlockSpeedLevel(int level);
private:
	PhysicsBody* physics;
	PhysicsBody* blockBody;
	int blockSpeedLevel;
	std::string status = "active";

};

#endif // !__BLOCK_H__