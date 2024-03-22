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
    _player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
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

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::spawnBlocks), 0.50f);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::OnContactBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);


    return true;
}

void GameScene::spawnBlocks(float dt) {
    auto randomNum = Utilities::getInstance()->generateNumber(0, 13);
    auto block = Block::create("fb_object_block_1");
    auto spawnX = columnWidth / 2 + block->getContentSize().width/2 * randomNum;
    block->setAnchorPoint(Vec2(0, 0));
    block->setPosition(Vec2(spawnX, visibleSize.height / 1.3));
    this->addChild(block);
}

bool GameScene::OnContactBegan(cocos2d::PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody();
    auto bodyB = contact.getShapeB()->getBody();

    if (bodyA->getCategoryBitmask()==0x01 && bodyB->getCategoryBitmask()==0x02 ||
        bodyB->getCategoryBitmask() == 0x01 && bodyA->getCategoryBitmask() == 0x02)
    {
        CCLOG("Var");
        CCLOG("Var");
        CCLOG("Var");
        CCLOG("Var");
        CCLOG("Var");
        CCLOG("Var");
        CCLOG("Var");
        CCLOG("Var");
        CCLOG("Var");
    }
    return true;
}



void GameScene::setupPhysicBorder() {
    auto origin = Director::getInstance()->getVisibleOrigin();

    auto edgeBody = PhysicsBody::createEdgeBox(Size(visibleSize.width - columnWidth, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    edgeNode->setPhysicsBody(edgeBody);
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