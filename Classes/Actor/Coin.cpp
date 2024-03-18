#include "Coin.h"
#include "Scenes/GameScene.h"

USING_NS_CC;

Coin* Coin::create() {
    auto newObject = new Coin();
    if (newObject != nullptr && newObject->init() ){

        newObject->autorelease();
        return newObject;
    }
    CC_SAFE_DELETE(newObject);
    return nullptr;
}

bool Coin::init()
{
    if (!Sprite::initWithFile("object/fb_object_coin.png"))
    {
        return false;
    }
   
    if (addPhysics()!=true)
    {
        CCLOG("add physics coin failed");
    }

    this->scheduleUpdate();

    return true;
}

bool Coin::addPhysics()
{
    physics = PhysicsBody::createBox(this->getContentSize());
    if (physics==nullptr)
    {
        CCLOG("add physics coin failed");
        return false;
    }
    physics->setDynamic(false);
    return true;
}
