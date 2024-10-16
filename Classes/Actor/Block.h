#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "cocos2d.h"
#include "Utilities/Utilities.h"
#include "AudioEngine/AudioEngine.h"
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
	float getPosX() { return posX; }
	void setPosX(float pos) { posX = pos; }
	float baseSpeed = 0;

private:
	Utilities* audioEngine;
	PhysicsBody* physics;
	PhysicsBody* blockBody;
	int blockSpeedLevel;
	std::string status = "active";
	float posX;
	bool isOnGround = false;
	void update(float dt);	
	Sprite* underBlock;
};

#endif // !__BLOCK_H__