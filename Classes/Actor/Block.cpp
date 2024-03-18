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
    if (!Sprite::initWithFile("object/"+tyleBlock+".png"))
    {
        return false;
    }

    if (addPhysics() != true)
    {
        CCLOG("add physics Block failed");
    }

    this->scheduleUpdate();

    return true;
}

bool Block::addPhysics()
{
    physics = PhysicsBody::createBox(this->getContentSize());
    physics->setMass(5.0f);
    if (physics == nullptr)
    {
        CCLOG("add physics Block failed");
        return false;
    }
    physics->setDynamic(true);
    return true;
}
