#include "./Life.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Life* Life::create() {
    auto newObject = new Life();
    if (newObject != nullptr && newObject->init()) {

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Life::init()
{
    if (!Sprite::initWithFile("object/fb_object_coin.png"))
    {
        return false;
    }

    if (addPhysics() != true)
    {
        CCLOG("add physics coin failed");
    }

    Utilities::getInstance()->loadSpriteFrameCache("animation/", "life_spawn");
    auto lifeAnimation = Utilities::createAnimation("life_spawn", 20, 0.05f);
    this->runAction(RepeatForever::create(Animate::create(lifeAnimation)));

    return true;
}

bool Life::addPhysics()
{
    physics = PhysicsBody::createBox(this->getContentSize());
    if (physics == nullptr)
    {
        CCLOG("add physics coin failed");
        return false;
    }
    physics->setDynamic(false);
    return true;
}