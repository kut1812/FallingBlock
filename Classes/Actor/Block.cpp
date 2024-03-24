#include "Block.h"
#include "Scenes/GameScene.h"

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

bool Block::addPhysics()
{
    Vec2 lowerEdge[4] = {
     Vec2(-this->getContentSize().width / 2,-this->getContentSize().height / 2 - 10),
     Vec2(-this->getContentSize().width / 2,0),
     Vec2(this->getContentSize().width / 2 ,-this->getContentSize().height / 2 - 10),
     Vec2(this->getContentSize().width / 2 ,0)
    };
    blockBody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.1f, 0.1f, 1.0f));
    blockBody->setDynamic(true);
    blockBody->setMass(50);
    blockBody->setRotationEnable(false);
    blockBody->setContactTestBitmask(5);
    blockBody->setCollisionBitmask(30);
    blockBody->setVelocity(Vec2(0, -90));

    auto edgeShape = PhysicsShapePolygon::create(lowerEdge, 4, PhysicsMaterial(0.1f, 0.1f, 1.0f));
    edgeShape->setCollisionBitmask(20);
    edgeShape->setContactTestBitmask(true);
    edgeShape->setTag(5);
    blockBody->addShape(edgeShape);
    this->addComponent(blockBody);

    return true;

}

void Block::setFlop() {
    blockBody->setVelocity(Vec2(0, -2600));
}