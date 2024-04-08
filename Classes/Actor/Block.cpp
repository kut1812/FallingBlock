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
    audioEngine = Audio::getInstance();
    this->setScale(0.48);
    if (addPhysics() != true)
    {
        CCLOG("add physics Block failed");
    }

    this->scheduleUpdateWithPriority(0);
    return true;
}

void Block::setBlockSpeedLevel(int level) {
    blockBody->setVelocity(Vec2(0, baseSpeed - level / 6));
}

bool Block::addPhysics()
{
    Vec2 lowerEdge[4] = {
     Vec2(-this->getContentSize().width / 3,-this->getContentSize().height / 2 ),
     Vec2(-this->getContentSize().width / 3,-10),
     Vec2(this->getContentSize().width / 3 ,-this->getContentSize().height / 2 ),
     Vec2(this->getContentSize().width / 3 ,-10)
    };
    blockBody = PhysicsBody::createBox(this->getContentSize(), PhysicsMaterial(10.0f, 0.0f, 1.0f));
    blockBody->setDynamic(true);
    blockBody->setMass(2);
    blockBody->setRotationEnable(false);
    blockBody->setContactTestBitmask(true);
    blockBody->setCollisionBitmask(30);
    blockBody->setVelocity(Vec2(0, baseSpeed - this->blockSpeedLevel / 6));
    blockBody->retain();

    this->addComponent(blockBody);
    audioEngine->play2d("Sounds/tray_exit.mp3", false);
    return true;

}

void Block::setFlop() {
    blockBody->setVelocity(Vec2(0, -10000));
}
void Block::update(float dt)
{
    if (this->getPositionX() != this->getPosX())
    {
        this->setPositionX(this->getPosX());
    }
    if (this->getPhysicsBody()->getVelocity().y <= 0 && this->getPhysicsBody()->getVelocity().y >= -3.0f && !isOnGround) {
        isOnGround = true;
        audioEngine->play2d("Sounds/9.mp3", false, 0.12f);
        Utilities::getInstance()->loadSpriteFrameCache("animation/", "block_falled");
        auto sfx_block_falled = Utilities::createAnimation("block_falled", 19, 0.1f);
        underBlock = Sprite::create("animation/block_falled_sprite.png");
        underBlock->setScale(2);
        underBlock->setPosition(Vec2(this->getContentSize().width/2, 0));
        this->addChild(underBlock);
        underBlock->runAction(Animate::create(sfx_block_falled));
    }
}