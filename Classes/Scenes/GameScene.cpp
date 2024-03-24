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

    auto uiButton = CSLoader::getInstance()->createNode("csb/ButtonGameScene.csb");
    this->addChild(uiButton,100);

    auto pause = uiButton->getChildByName<ui::Button*>("Button_3");
    pause->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->addChild(LayerManager::getInstance()->pauseLayer(), 100);
        }
        });
    //button x2coin
    auto coinDouble = uiButton->getChildByName<ui::Button*>("Button_4");
    coinDouble->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //thêm sự kiện
        }
        });
    //button shield
    auto shield = uiButton->getChildByName<ui::Button*>("Button_5");
    shield->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //thêm sự kiện
        }
        });
    //button doubleJump
    auto doubleJump = uiButton->getChildByName<ui::Button*>("Button_6");
    doubleJump->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //thêm sự kiện
        }
        });
    //button upgrade
    auto upgrade = uiButton->getChildByName<ui::Button*>("Button_1");
    upgrade->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //thêm sự kiện
        }
        });
    //button shop
    auto shop = uiButton->getChildByName<ui::Button*>("Button_1");
    shop->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //thêm sự kiện
        }
        });
    //label life
    auto life = uiButton->getChildByName<Label*>("Text_1");
    //label height
    auto height = uiButton->getChildByName<Label*>("Text_2");
     //label coin
    auto coin = uiButton->getChildByName<Label*>("Text_3");
     //label x2jump
    auto x2jump = uiButton->getChildByName<Label*>("Text_4");
     //label shield
    auto textShield = uiButton->getChildByName<Label*>("Text_5");
     //label x2coin
    auto x2coin = uiButton->getChildByName<Label*>("Text_6");
    

    GameScene::setupPhysicBorder();
    Utilities::getInstance()->initRandomSeed();

    _player = Player::createPlayer();
    _player->setPosition(Vec2(visibleSize.width / 2, 2));
    this->addChild(_player, 5);

    _joystick = Joystick::create();
    if (_joystick)
        this->addChild(_joystick, 5000);
    _joystick->setPosition(visibleSize.width / 8, visibleSize.height *0.15);

    _jumpButton = JumpButton::create();
    if (_jumpButton) {
        this->addChild(_jumpButton, 5000);
    }
    _jumpButton->setPosition(visibleSize.width *0.85, visibleSize.height *0.15);

    this->schedule([this](float dt) {
        GameScene::updatePlayer(dt);
        }, "update_player");

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::spawnBlocks), 2.50f);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateMeter), 0.0f);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateCoin), 10.0f);


    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::OnContactBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    mileageCounter = MileageCounter::create("font/Baloo2/Baloo2-Bold.ttf", std::to_string(0), 24);
    mileageCounter->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    this->addChild(mileageCounter, 1999);

    return true;
}

void GameScene::spawnBlocks(float dt) {
    auto randomQuantityBlock = Utilities::getInstance()->generateNumber(1, 3);
    int count = 0;
    do {
        auto randomNum = Utilities::getInstance()->generateNumber(0, 13);
        while (listPositionYBlock[randomNum] - findMin(listPositionYBlock, 14) >= 3)
        {
            randomNum = Utilities::getInstance()->generateNumber(0, 13);
        }
        listPositionYBlock[randomNum] += 1;

        auto randomTyle = Utilities::getInstance()->generateNumber(0, 3);

        Block* block;
        if (randomTyle == 0)
        {
            block = Block::create("fb_object_block_1");
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
        blockSize = Size(block->getContentSize());
        block->setAnchorPoint(Vec2(0, 0));
        block->setPosition(Vec2(spawnX, visibleSize.height / 1.3));
        this->addChild(block);
        listOfBlocks.push_back(block);

        listOfBlocks.push_back(block);

        count++;
    } while (count <= randomQuantityBlock);

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


    return true;
}

void GameScene::setupPhysicBorder() {
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto edgeBody = PhysicsBody::createEdgeBox(Size(visibleSize.width - columnWidth, visibleSize.height), PHYSICSBODY_MATERIAL_DEFAULT, 3);
    edgeBody->setCategoryBitmask(0x08);
    edgeBody->setCollisionBitmask(0x07);
    edgeBody->setContactTestBitmask(0x07);
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
            _player->increaseJumpCount();
            _jumpButton->resetPressed();
        }
    }

    // update player move and jump action
    if (_player) {
        _player->setDirection(_joystick->getDirection());
        float s = visibleSize.width - (columnWidth / 2);
        _player->update(dt, columnWidth / 2, s);
    }

    // contact with coin
    if (!listOfCoins.empty()) {
        std::vector<Coin*> listRemoveCoin;
        for (auto coin : listOfCoins) {
            if (coin->getBoundingBox().containsPoint(_player->getPosition())) {
                coin->removeFromParentAndCleanup(true);
                listRemoveCoin.push_back(coin);
                if (!_player->isX2Coin())
                    CoinManager::getInstance()->increaseCoins(1);
                else
                    CoinManager::getInstance()->increaseCoins(1 * 2);
            }
        }
        for (auto coin : listRemoveCoin) {
            auto it = std::find(listOfCoins.begin(), listOfCoins.end(), coin);
            if (it != listOfCoins.end()) {
                listOfCoins.erase(it);
            }
        }
    }
    /*for (auto coin : listOfCoins) {
        coin->setPositionY(visibleSize.height - coin->getPositionY());
    }
    */
}

void GameScene::updateCoin(float dt) {
    if (blockSize.width != 0 && blockSize.height != 0) {
        auto randomQuantityCoin = Utilities::getInstance()->generateNumber(2, 5);
        int count = 0;
        do {
            auto randomX = Utilities::getInstance()->generateNumber(0, 16);
            auto randomY = Utilities::getInstance()->generateNumber(3, 16);
            auto spawnX = columnWidth / 2 + blockSize.width / 2 * randomX;
            auto spawnY = blockSize.height / 2 * randomY;
            Rect coinRect(Vec2(spawnX, spawnY), blockSize);
            while (coinRect.containsPoint(Vec2(spawnX, spawnY))) {
                auto randomX = Utilities::getInstance()->generateNumber(0, 16);
                auto randomY = Utilities::getInstance()->generateNumber(3, 16);
                spawnX = columnWidth / 2 + blockSize.width / 2 * randomX;
                spawnY = blockSize.height / 2 * randomY;
            }

            auto coin = Coin::create();
            coin->setPosition(spawnX, spawnY);
            this->addChild(coin, 1000);
            listOfCoins.push_back(coin);

            count++;
        } while (count <= randomQuantityCoin);
    }
}