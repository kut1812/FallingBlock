#include "cocostudio/CocoStudio.h"
#include "LayerManager.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "Utilities/Utilities.h"
USING_NS_CC;

Scene* GameScene::create()
{
    GameScene* scene = new GameScene();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
}

bool GameScene::init()
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    this->getPhysicsWorld()->setGravity(Vec2(0, -980));

    auto uiMenu = CSLoader::getInstance()->createNode("csb/Layer.csb");
    this->addChild(uiMenu);

    auto column = uiMenu->getChildByName<Sprite*>("block_16_0");
    columnWidth = column->getContentSize().width;

    auto pause = uiMenu->getChildByName<ui::Button*>("Button_3");
    pause->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->addChild(LayerManager::getInstance()->pauseLayer(), 100);
        }
        });

    GameScene::setupPhysicBorder();
    Utilities::getInstance()->initRandomSeed();

    _player = Player::createPlayer();
    _player->setPosition(Vec2(visibleSize.width / 2, 2));
    this->addChild(_player, 5);

    _joystick = Joystick::create();
    if (_joystick)
        this->addChild(_joystick, 5000);
    _joystick->setPosition(visibleSize.width / 8, visibleSize.height / 8);

    _jumpButton = JumpButton::create();
    if (_jumpButton) {
        this->addChild(_jumpButton, 5000);
    }
    _jumpButton->setPosition(visibleSize.width / 1.1, visibleSize.height / 8);

    this->schedule([this](float dt) {
        GameScene::updatePlayer(dt);
        }, "update_player");

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::spawnBlocks), 1.50f);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateMeter), 0.0f);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::OnContactBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    mileageCounter = MileageCounter::create("font/Baloo2/Baloo2-Bold.ttf", std::to_string(0), 24);
    mileageCounter->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(mileageCounter, 1999);
    return true;
}

void GameScene::spawnBlocks(float dt) {

    auto randomNum = Utilities::getInstance()->generateNumber(0, 13);
    while (listPositionYBlock[randomNum]-findMin(listPositionYBlock,14)>=3)
    {
        randomNum = Utilities::getInstance()->generateNumber(0, 13);
    }
    listPositionYBlock[randomNum] += 1;

    auto randomTyle = Utilities::getInstance()->generateNumber(0, 3);

    Block* block;
    if (randomTyle==0)
    {
        block= Block::create("fb_object_block_1");
    }
    else if (randomTyle == 1)
    {
        block = Block::create("fb_object_block_2");
    }
    else if (randomTyle == 2)
    {
        block = Block::create("fb_object_block_3");
    }
    else if (randomTyle == 3)
    {
        block = Block::create("fb_object_block_4");
    }
    auto spawnX = columnWidth / 2 + block->getContentSize().width / 2 * randomNum;
    block->setAnchorPoint(Vec2(0, 0));
    block->setPosition(Vec2(spawnX, visibleSize.height / 1.3));
    this->addChild(block);
    listOfBlocks.push_back(block);

}

void GameScene::updateMeter(float dt) {
    currentMeter = savedMeterBe4Reset + _player->getPositionY() / 10;
    mileageCounter->setMileage(currentMeter - 1);
    if (currentMeter > limitMeter && _player->getPositionY() <= (visibleSize.height - (visibleSize.height / 5)) && _player->getPhysicsBody()->getVelocity().y >= -0.5 && _player->getPhysicsBody()->getVelocity().y <= 0.5) {
        std::vector<Block*> listToRemove;
        for (auto i : listOfBlocks) {
            if (i->getPositionY() <= i->getSpriteSize().height && i->getPositionY() >= 0) {
                i->setFlop();
                listToRemove.push_back(i);
            }
        }
        limitMeter += 20;
        savedMeterBe4Reset = currentMeter - ((currentMeter - limitMeter) > currentMeter ? (currentMeter - limitMeter) : 0);
    }
}

bool GameScene::OnContactBegan(cocos2d::PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody()->getNode();
    auto bodyB = contact.getShapeB()->getBody()->getNode();

    if (bodyA->getPhysicsBody()->getCollisionBitmask() == 10 && bodyB->getPhysicsBody()->getShape(5)->getCollisionBitmask() == 20 ||
        bodyA->getPhysicsBody()->getShape(5)->getCollisionBitmask() == 20 && bodyB->getPhysicsBody()->getCollisionBitmask() == 10
        )
    {
        CCLOG("lose");
    }

  /*  if (bodyA->getPhysicsBody()->getCollisionBitmask() == 30 && bodyB->getPhysicsBody()->getShape(5)->getCollisionBitmask() == 20)
    {
        auto block = bodyB->getPhysicsBody()->getNode();
        auto anim = Sprite::create("animation/block_falled (1).png");
        anim->runAction(Animate::create(AnimationCache::getInstance()->getAnimation("MOVE_ANIM")));
        block->addChild(anim);

    }
    if (bodyB->getPhysicsBody()->getCollisionBitmask() == 30 && bodyA->getPhysicsBody()->getShape(5)->getCollisionBitmask() == 20)
    {
        CCLOG("lose");
    }*/

    return true;
}

void GameScene::setupPhysicBorder() {
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto edgeBody = PhysicsBody::createEdgeBox(Size(visibleSize.width - columnWidth, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCategoryBitmask(0x08);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    edgeNode->addComponent(edgeBody);
    this->addChild(edgeNode);
}

void GameScene::updatePlayer(float dt) {
    // update move action
    if (_joystick) {
        if (_joystick->getDirection().x > 0) {
            _player->changeState(Player::PlayerState::MOVE_RIGHT);
        }
        else if (_joystick->getDirection().x < 0) {
            _player->changeState(Player::PlayerState::MOVE_LEFT);
        }
        else {
            _player->changeState(Player::PlayerState::IDLE);
        }
    }

    // update jump action
    if (_jumpButton) {
        if (_jumpButton->getIsPress()) {
            _player->setJump(true);
        }
        else {
            _player->setJump(false);
        }
    }

    // update player move and jump action
    if (_player) {
        _player->setDirection(_joystick->getDirection());
        float s = visibleSize.width - (columnWidth / 2);
        _player->update(dt, columnWidth / 2, s);
    }

}