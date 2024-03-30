#include "Block.h"
#include "Scenes/GameScene.h"
#include "WorkingWithData/SQLiteManager.h"
USING_NS_CC;

Block* Block::create(std::string tyleBlock) {
    auto newObject = new Block();
    if (newObject != nullptr && newObject->init(tyleBlock)) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Block::init(std::string tyleBlock)
{
    if (!Sprite::initWithFile("object/" + tyleBlock + ".png"))
    {
        return false;
    }
    this->setScale(0.48);
    if (addPhysics() != true)
    {
        CCLOG("add physics Block failed");
    }

    this->scheduleUpdate();
    return true;
}

void Block::setBlockSpeedLevel(int level) {
    blockBody->setVelocity(Vec2(0, 100 - level / 6));
}

bool Block::addPhysics()
{
    Vec2 lowerEdge[4] = {
     Vec2(-this->getContentSize().width / 3,-this->getContentSize().height / 2 ),
     Vec2(-this->getContentSize().width / 3,-10),
     Vec2(this->getContentSize().width / 3 ,-this->getContentSize().height / 2 ),
     Vec2(this->getContentSize().width / 3 ,-10)
    };
    blockBody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(1.0f, 0.1f, 1.0f));
    blockBody->setDynamic(true);
    blockBody->setMass(30);
    blockBody->setRotationEnable(false);
    blockBody->setContactTestBitmask(true);
    blockBody->setCollisionBitmask(30);
    blockBody->setVelocity(Vec2(0, 100 - this->blockSpeedLevel / 6));
    blockBody->retain();
    this->addComponent(blockBody);

    return true;

}

void Block::setFlop() {
    blockBody->setVelocity(Vec2(0, -2600));
}
void Block::update(float dt)
{
    if (this->getPositionX() != this->getPosX())
    {
        this->setPositionX(this->getPosX());
    }
}