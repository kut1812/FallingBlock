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
    this->setScale(0.49);
    if (addPhysics() != true)
    {
        CCLOG("add physics Block failed");
    }

    this->scheduleUpdate();

    return true;
}

bool Block::addPhysics()
{
    auto blockBody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(0.1f, 0.5f, 0.1f));
    blockBody->setDynamic(true); 
    blockBody->setMass(500.0f);
    blockBody->setRotationEnable(false);

    Vec2 lowerEdge[2] = {
        Vec2(-this->getContentSize().width / 2+10, -this->getContentSize().width / 2+10),
        Vec2(this->getContentSize().width/2-10, -this->getContentSize().width / 2+10)
    };
    auto edgeShape = PhysicsShapeEdgePolygon::create(lowerEdge, 2, PhysicsMaterial(0.1f, 0.5f, 0.1f));
    edgeShape->setCategoryBitmask(0x01);
    edgeShape->setCollisionBitmask(0x02);
    edgeShape->setContactTestBitmask(0x02);/*
    auto node = Node::create();
    node->setPhysicsBody(edgeShape)*/;
    blockBody->addShape(edgeShape);
    //this->addChild(node);
    this->setPhysicsBody(blockBody);

    // Gán PhysicsBody vào Sprite
    return true;
}