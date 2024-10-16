﻿#include "cocostudio/CocoStudio.h"
#include "LayerManager.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "Utilities/Utilities.h"
#include "LayerManager.h"
#include "UpgradeLayer.h"
#include "StoreLayer.h"
USING_NS_CC;

Scene* GameScene::create(Player* _plr)
{
    GameScene* scene = new GameScene();
    if (scene && scene->init(_plr))
    {

        scene->dbManager = SQLiteManager::getInstance();
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
}

bool GameScene::init(Player* _plr)
{
    if (!Scene::initWithPhysics())
    {
        return false;
    }
     //this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    visibleSize = Director::getInstance()->getVisibleSize();
    audioEngine = Utilities::getInstance();
    _player = _plr;
    _player->setPosition(Vec2(visibleSize.width / 2, 100));
    _player->setTag(909);
    this->addChild(_player, 1);
    CoinManager::getInstance()->reset();
    this->getPhysicsWorld()->setGravity(Vec2(0, -700));

    auto uiMenu = CSLoader::getInstance()->createNode("csb/Layer.csb");
    this->addChild(uiMenu);

    auto column = uiMenu->getChildByName<Sprite*>("block_16_0");
    columnWidth = column->getContentSize().width;

    auto uiButton = CSLoader::getInstance()->createNode("csb/ButtonGameScene.csb");
    this->addChild(uiButton, 3);

    auto pause = uiButton->getChildByName<ui::Button*>("Button_3");
    pause->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            pause->setScale(0.55f);
            break;
        case ui::Widget::TouchEventType::ENDED:
            setDynamicAllBlock(false);
            pause->setScale(0.5f);
            this->addChild(LayerManager::getInstance()->pauseLayer(), 100);
            break;
        default:
            break;
        }
        });

    // Button x2coin
    auto coinDouble = uiButton->getChildByName<ui::Button*>("Button_4");
    coinDouble->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Button::TouchEventType::BEGAN: {
            if (_player->getX2Coin() && _player->getCoinAmount() > 0 && _player->getX2Coin()->getSkillCooldown()<=0)
            {

            coinDouble->setScale(0.55f);
            }
            break;
        }
        case ui::Button::TouchEventType::ENDED:
            if (_player->getX2Coin() && _player->getCoinAmount() > 0 && _player->getX2Coin()->use()) {
                audioEngine->playSFX("Sounds/tap_digits.mp3");
                _player->decreaseCoinAmount(1);
                dbManager->setPlayerInfo(1, _player->getMovementLevel(), _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), _player->getCoinAmount(), _player->getJumpAmount(), _player->getShieldAmount());
                skillSpriteCoin = Sprite::create("control/fb_ctrl_skill_dup_coin_wait.png");
                skillSpriteCoin->setPosition(Vec2(visibleSize.width * 0.77, visibleSize.height * 0.15));
                skillSpriteCoin->setScale(0.5);
                Director::getInstance()->getRunningScene()->addChild(skillSpriteCoin, 3);

                auto label = Label::createWithTTF(StringUtils::format("%.1f", _player->getX2Coin()->getMaxSkillCooldown()), "font/Baloo2/Baloo2-Bold.ttf", 24);
                label->setPosition(skillSpriteCoin->getPosition());
                Director::getInstance()->getRunningScene()->addChild(label, 3);

                float remainingCooldown = _player->getX2Coin()->getMaxSkillCooldown();

                Director::getInstance()->getScheduler()->schedule([=](float dt) mutable {
                    remainingCooldown -= dt;
                    label->setString(StringUtils::format("%.1f", remainingCooldown));

                    if (remainingCooldown <= 0) {
                        label->removeFromParent();
                    }
                    }, label, 0.1f, kRepeatForever, 0.0f, false, "cooldown_scheduler1");
            }
            coinDouble->setScale(0.5);
            break;
        default:
            break;
        }
        if (!_player->getX2Coin()) coinDouble->setVisible(false);
        });

    // Button shield
    auto shield = uiButton->getChildByName<ui::Button*>("Button_5");
    shield->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Button::TouchEventType::BEGAN: {
            if (_player->getShield() && _player->getShieldAmount() > 0 && _player->getShield()->getSkillCooldown()<=0)
            {

            shield->setScale(0.55f);
            }
            break;
        }
        case ui::Button::TouchEventType::ENDED:
            shield->setScale(0.5);
            if (_player->getShield() && _player->getShieldAmount() > 0 && _player->getShield()->use()) {
                audioEngine->playSFX("Sounds/tap_digits.mp3");
                _player->decreaseShieldAmount(1);
                dbManager->setPlayerInfo(1, _player->getMovementLevel(), _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), _player->getCoinAmount(), _player->getJumpAmount(), _player->getShieldAmount());
                skillSpriteShield = Sprite::create("control/fb_ctrl_skill_dup_coin_wait.png");
                skillSpriteShield->setPosition(Vec2(visibleSize.width * 0.79, visibleSize.height * 0.27));
                skillSpriteShield->setScale(0.5);

                Director::getInstance()->getRunningScene()->addChild(skillSpriteShield, 3);

                auto label = Label::createWithTTF(StringUtils::format("%.1f", _player->getShield()->getMaxSkillCooldown()), "font/Baloo2/Baloo2-Bold.ttf", 24);
                label->setPosition(skillSpriteShield->getPosition());
                Director::getInstance()->getRunningScene()->addChild(label, 3);

                float remainingCooldown = _player->getShield()->getMaxSkillCooldown();

                Director::getInstance()->getScheduler()->schedule([=](float dt) mutable {
                    remainingCooldown -= dt;
                    label->setString(StringUtils::format("%.1f", remainingCooldown));

                    if (remainingCooldown <= 0) {
                        label->removeFromParent();
                    }
                    }, label, 0.1f, kRepeatForever, 0.0f, false, "cooldown_scheduler2");
            }
            break;
        default:
            break;
        }
        if (!_player->getShield()) shield->setVisible(false);
        });

    // Button doubleJump
    auto doubleJump = uiButton->getChildByName<ui::Button*>("Button_6");
    doubleJump->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Button::TouchEventType::BEGAN: {
            if (_player->getX2Jump() && _player->getJumpAmount() > 0 && _player->getX2Jump()->getSkillCooldown()<=0) {

            doubleJump->setScale(0.55f);
            }
            break;
        }
        case ui::Button::TouchEventType::ENDED:
            doubleJump->setScale(0.5);
            if (_player->getX2Jump() && _player->getJumpAmount() > 0 && _player->getX2Jump()->use()) {
                audioEngine->playSFX("Sounds/tap_digits.mp3");
                _player->decreaseJumpAmount(1);
                dbManager->setPlayerInfo(1, _player->getMovementLevel(), _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), _player->getCoinAmount(), _player->getJumpAmount(), _player->getShieldAmount());
                skillSpriteJump = Sprite::create("control/fb_ctrl_skill_dup_coin_wait.png");
                skillSpriteJump->setPosition(Vec2(visibleSize.width * 0.85, visibleSize.height * 0.32));
                skillSpriteJump->setScale(0.5);
                Director::getInstance()->getRunningScene()->addChild(skillSpriteJump, 3);

                auto label = Label::createWithTTF(StringUtils::format("%.1f", _player->getX2Jump()->getMaxSkillCooldown()), "font/Baloo2/Baloo2-Bold.ttf", 24);
                label->setPosition(skillSpriteJump->getPosition());
                Director::getInstance()->getRunningScene()->addChild(label, 3);

                float remainingCooldown = _player->getX2Jump()->getMaxSkillCooldown();

                Director::getInstance()->getScheduler()->schedule([=](float dt) mutable {
                    remainingCooldown -= dt;
                    label->setString(StringUtils::format("%.1f", remainingCooldown));

                    if (remainingCooldown <= 0) {
                        label->removeFromParent();
                    }
                    }, label, 0.1f, kRepeatForever, 0.0f, false, "cooldown_scheduler3");
            }
            break;
        default:
            break;
        }
        if (!_player->getX2Jump()) doubleJump->setVisible(false);
        });

    // Button Upgrade
    auto upgrade = uiButton->getChildByName<ui::Button*>("Button_1");
    upgrade->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            upgrade->setScale(0.55f);
            break;
        case ui::Widget::TouchEventType::ENDED:
            upgrade->setScale(0.5f);
            setDynamicAllBlock(false);
            audioEngine->playSFX("Sounds/tap_digits.mp3");
            auto upgradeLayer = UpgradeLayer::create(_player);
            this->addChild(upgradeLayer, 3);
            break;
        }
        });

    // Button Shop
    auto shop = uiButton->getChildByName<ui::Button*>("Button_2");
    shop->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type) {
        case ui::Widget::TouchEventType::BEGAN:
            shop->setScale(0.55f);
            break;
        case ui::Widget::TouchEventType::ENDED:
            setDynamicAllBlock(false);
            shop->setScale(0.5f);
            audioEngine->playSFX("Sounds/tap_digits.mp3");
            auto storeLayer = StoreLayer::create(_player);
            this->addChild(storeLayer, 4);
            break;
        }
        });

    //label life
    lifeLabel = Label::createWithTTF(std::to_string(_player->getSpawnLife()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    lifeLabel->setPosition(Vec2(visibleSize.width*0.24,visibleSize.height*0.92));
    this->addChild(lifeLabel,3);    
    //label coin
    coin = Label::createWithTTF(std::to_string(_player->getMoney()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    coin->setPosition(Vec2(visibleSize.width * 0.44, visibleSize.height * 0.92));
    this->addChild(coin, 3);
    //label x2jump
    x2jump = Label::createWithTTF(std::to_string(_player->getJumpAmount()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    x2jump->setPosition(Vec2(visibleSize.width * 0.53, visibleSize.height * 0.92));
    this->addChild(x2jump, 3);
    //label shield
    textShield = Label::createWithTTF(std::to_string(_player->getShieldAmount()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    textShield->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.92));
    this->addChild(textShield, 3);
    //label x2coin
    x2coin = Label::createWithTTF(std::to_string(_player->getCoinAmount()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    x2coin->setPosition(Vec2(visibleSize.width * 0.67, visibleSize.height * 0.92));
    this->addChild(x2coin, 3);

    //sprite disable coin
    disableSpriteCoin = Sprite::create("control/fb_ctrl_skill_dup_coin_block.png");
    disableSpriteCoin->setPosition(Vec2(visibleSize.width*0.77,visibleSize.height*0.15));
    disableSpriteCoin->setScale(0.5);
    this->addChild(disableSpriteCoin,4);
    //sprite disable jump
    disableSpriteJump = Sprite::create("control/fb_ctrl_skill_dup_jump_block.png");
    disableSpriteJump->setPosition(Vec2(visibleSize.width*0.85,visibleSize.height*0.32));
    disableSpriteJump->setScale(0.5);
    this->addChild(disableSpriteJump,4);
    //sprite disable shield
    disableSpriteShield = Sprite::create("control/fb_ctrl_skill_sheild_block.png");
    disableSpriteShield->setPosition(Vec2(visibleSize.width*0.79,visibleSize.height*0.27));
    disableSpriteShield->setScale(0.5);
    this->addChild(disableSpriteShield,4);


    GameScene::setupPhysicBorder();
    Utilities::getInstance()->initRandomSeed();

    _joystick = Joystick::create();
    if (_joystick)
        this->addChild(_joystick, 1);
    _joystick->setPosition(visibleSize.width / 8, visibleSize.height * 0.25);

    _jumpButton = JumpButton::create();
    if (_jumpButton) {
        this->addChild(_jumpButton, 1);
    }
    _jumpButton->setPosition(visibleSize.width * 0.85, visibleSize.height * 0.15);

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updatePlayer), 0.0f);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::spawnCoins), 0.0f);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::spawnBlocks), 5.0f);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateMeter), 0.0f);
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updateCoin), 0.0f);

    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::OnContactBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    mileageCounter = MileageCounter::create("font/Baloo2/Baloo2-Bold.ttf", std::to_string(0), 20);
    uiButton->addChild(mileageCounter, 1999);
    mileageCounter->setPosition(visibleSize.width * 0.33, visibleSize.height * 0.92);

    for (int i = 0; i < 28; i++) {
        if (i <= 13) {
            Block* block = Block::create("fb_object_block_1");
            block->setAnchorPoint(Vec2(0,0));
            block->setPosition(Vec2(0, 0));
            block->setPosX(columnWidth / 2 + i * (block->getContentSize().width / 2));
            this->addChild(block);
            listOfBlocks.push_back(block);
        }
        else {
            Block* block = Block::create("fb_object_block_2");
            block->setAnchorPoint(Vec2(0, 0));
            block->setPosition(Vec2(0, block->getContentSize().height / 2));
            block->setPosX(columnWidth / 2 + (i - 14) * (block->getContentSize().width / 2));
            this->addChild(block);
            listOfBlocks.push_back(block);
        }
    }
    lifeSpawn = Life::create();
    lifeSpawn->setPosition(_player->getPosition() + Vec2(0, 60));
    this->addChild(lifeSpawn);
    if (_player) { 
        this->schedule(CC_SCHEDULE_SELECTOR(GameScene::spawnLife), _player->getSpawnTime(), CC_REPEAT_FOREVER, 0.0f);
    }
    return true;
}

void GameScene::spawnLife(float dt) {
    if (lifeSpawn) { lifeSpawn->removeFromParentAndCleanup(true); lifeSpawn = nullptr; }
    lifeSpawn = Life::create();
    lifeSpawn->setPosition(_player->getPosition() + Vec2(0, 60));
    this->addChild(lifeSpawn);
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
            block->setBlockSpeedLevel(_player->getBlockSpeedLevel());
        }
        else if (randomTyle == 1)
        {
            block = Block::create("fb_object_block_2");
            block->setBlockSpeedLevel(_player->getBlockSpeedLevel());
        }
        else if (randomTyle == 2)
        {
            block = Block::create("fb_object_block_3");
            block->setBlockSpeedLevel(_player->getBlockSpeedLevel());
        }
        else if (randomTyle == 3)
        {
            block = Block::create("fb_object_block_4");
            block->setBlockSpeedLevel(_player->getBlockSpeedLevel());
        }
        block->setTag(randomNum);
        auto spawnX = columnWidth / 2 + block->getContentSize().width / 2 * randomNum;
        blockSize = Size(block->getContentSize());
        block->setPosX(spawnX);
        block->setAnchorPoint(Vec2(0, 0));
        block->setPosition(Vec2(spawnX, visibleSize.height + block->getContentSize().height));
        this->addChild(block);
        block->baseSpeed = block->baseSpeed + (dt * 0.0003);
        listOfBlocks.push_back(block);
        count++;
    } while (count <= randomQuantityBlock);
}

void GameScene::spawnCoins(float dt)
{
    float myFloat = std::atof(mileageCounter->getString().c_str());
    if (myFloat-minSpawnCoin>=0)
    {
        minSpawnCoin += 50;
        auto quantityCoin = Utilities::getInstance()->generateNumber(3, 6);
        for (int i = 0; i < quantityCoin; i++)
        {
        auto coin = Coin::create();
        coin->setScale(100.f/75.f/3);
        auto randomX = Utilities::getInstance()->generateNumber(0, 19);
        auto randomY = Utilities::getInstance()->generateNumber(2, 8);
        auto spawnX = columnWidth / 2 + coin->getContentSize().width / 2 * randomX;
        float a = randomY;
        int posY = a / 10 * visibleSize.height;
        CCLOG("%d", posY);
        coin->setPosition(Vec2(spawnX,posY));
        coin->setAnchorPoint(Vec2(0, 0));
        this->addChild(coin,2);
        listOfCoins.push_back(coin);
        }
    }
}

void GameScene::setDynamicAllBlock(bool x)
{
    for (auto i : listOfBlocks) {
        if (i != nullptr&&i->getPhysicsBody()!=nullptr && _player->getParent()==this && i->getParent()==this)
        {
            i->getPhysicsBody()->setDynamic(x);
        }
    }
}

void GameScene::updateMeter(float dt) {
    if (_player) {
        currentMeter = savedMeterBe4Reset + _player->getPositionY() / 10;
        float myFloat = std::atof(mileageCounter->getString().c_str());
        if (currentMeter - 2 > myFloat)
        {
            mileageCounter->setMileage(currentMeter - 11);
        }
        if (currentMeter > limitMeter && _player->getPositionY() <= (visibleSize.height - (visibleSize.height / 5)) && _player->getPhysicsBody()->getVelocity().y >= -0.1 && _player->getPhysicsBody()->getVelocity().y <= 0.1) {
            std::vector<Block*> listToRemove;
            int count = 0;
            for (auto i : listOfBlocks) {
                if (i->getPositionY() <= 4 && count <= checkFlop) {
                    i->setFlop();
                    listToRemove.push_back(i);
                    i->setVisible(false);
                    count++;
                }
            }
            checkFlop += 13;
            limitMeter += 25;
            savedMeterBe4Reset = currentMeter - ((currentMeter - limitMeter) > currentMeter ? (currentMeter - limitMeter) : 0);
        for (auto c : listOfCoins)
        {
            auto moveBy = MoveBy::create(0.2f, Vec2(0, -blockSize.height));
            c->runAction(moveBy);
        }
        }
    }
}

bool GameScene::OnContactBegan(cocos2d::PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody()->getNode();
    auto bodyB = contact.getShapeB()->getBody()->getNode();

    if (bodyA && bodyB) {
        if (_player->getParent() == this && bodyA != nullptr && bodyA->getPhysicsBody() != nullptr && bodyB != nullptr && bodyB->getPhysicsBody() != nullptr)
        {
            if (bodyA->getPosition().x > 1 && bodyB->getPosition().x > 1)
            {

                if (bodyA->getPhysicsBody()->getCollisionBitmask() == 30 && bodyB->getPhysicsBody()->getCollisionBitmask() == 10 ||
                    bodyA->getPhysicsBody()->getCollisionBitmask() == 10 && bodyB->getPhysicsBody()->getCollisionBitmask() == 30
                    )
                {

                    _player->getPhysicsBody()->setVelocity(Vec2(0, 0));
                    CCLOG("having contact %f %f", _player->getDirection().x, _player->getDirection().y);
                }
            }
        }
        if (bodyA->getPhysicsBody() && bodyB->getPhysicsBody() && bodyA->getPhysicsBody()->getCollisionBitmask() == 30 && bodyB->getPhysicsBody()->getCollisionBitmask() == 11 ||
            bodyA->getPhysicsBody() && bodyB->getPhysicsBody() && bodyA->getPhysicsBody()->getCollisionBitmask() == 11 && bodyB->getPhysicsBody()->getCollisionBitmask() == 30
            )
        {
            if(_player->getSpawnLife() <= 1) {
                audioEngine->playSFX("Sounds/6.mp3");
                for (auto i : listOfBlocks) {
                    if (i != nullptr && i->getPhysicsBody() != nullptr && _player->getParent() == this && i->getParent() == this)
                    {
                        i->removeAllComponents();
                    }
                }
                if (_player->getShield()) {
                    _player->getShield()->~ShieldSkill();

                    _player->resetSkill();
                }
                if (_player->getX2Jump()) {
                    _player->getX2Jump()->~X2JumpSkill();
                    _player->resetSkill();
                }
                if (_player->getX2Coin()) {
                    _player->getX2Coin()->~X2CoinSkill();
                    _player->resetSkill();
                }

                this->removeChild(_player);
                this->unscheduleAllCallbacks();
                // Trong hàm hiển thị layer "Lose"

                this->pause();
                auto score = MileageCounter::create("font/Baloo2/Baloo2-Bold.ttf", mileageCounter->getString(), 20);
                auto loseLayer = LayerManager::getInstance()->loseLayer(std::stoi(mileageCounter->getString()), _player);
                this->addChild(loseLayer, 4);
                loseLayer->addChild(score, 0);
                score->setPosition(Vec2(visibleSize.width * 0.51, visibleSize.height * 0.5));
            }
            else {
                _player->decreaseSpawnLife();
                audioEngine->playSFX("Sounds/6.mp3");
                if (bodyA->getPhysicsBody()->getCollisionBitmask() == 30) {
                    bodyA->getPhysicsBody()->onRemove();
                    bodyA->setVisible(false);
                    listPositionYBlock[bodyA->getTag()] -= 1;
                    auto it = std::find(listOfBlocks.begin(), listOfBlocks.end(), static_cast<Block*>(bodyA));
                    if (it != listOfBlocks.end()) {
                        listOfBlocks.erase(it);
                    }
                    bodyA->removeFromParent();
                }
                else if (bodyB->getPhysicsBody()->getCollisionBitmask() == 30) {
                    bodyB->getPhysicsBody()->onRemove();
                    bodyB->setVisible(false);
                    listPositionYBlock[bodyB->getTag()] -= 1;
                    auto it = std::find(listOfBlocks.begin(), listOfBlocks.end(), static_cast<Block*>(bodyB));
                    if (it != listOfBlocks.end()) {
                        listOfBlocks.erase(it);
                    }
                    bodyB->removeFromParent();
                }
            }
        }
    }

    return true;
}

void GameScene::setupPhysicBorder() {
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    bottomColumn = Node::create();
    bottomColumn->setPosition(Vec2(0,-visibleSize.height / 2));
    bottomColumn->setAnchorPoint(Vec2(0,0));
    bottomColumn->setContentSize(Size(visibleSize.width, 1));
    auto bottomBox = PhysicsBody::createBox(Size(visibleSize.width, visibleSize.height));
    bottomBox->setDynamic(false);
    bottomBox->setCategoryBitmask(15);
    bottomBox->setCollisionBitmask(15);
    bottomBox->setContactTestBitmask(true);
    bottomColumn->addComponent(bottomBox);
    this->addChild(bottomColumn);

    leftColumnNode = Node::create();
    leftColumnNode->setPosition(Vec2(0, visibleSize.height / 2));
    auto leftBox = PhysicsBody::createBox(Size(columnWidth-3, visibleSize.height));
    leftBox->setDynamic(false);
    leftBox->setCategoryBitmask(15);
    leftBox->setCollisionBitmask(15);
    leftBox->setContactTestBitmask(true);
    leftColumnNode->addComponent(leftBox);
    this->addChild(leftColumnNode);

    rightColumnNode = Node::create();
    rightColumnNode->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
    auto rightBox = PhysicsBody::createBox(Size(columnWidth-3, visibleSize.height));
    rightBox->setDynamic(false);
    rightBox->setCategoryBitmask(15);
    rightBox->setCollisionBitmask(15);  
    rightBox->setContactTestBitmask(true);
    rightColumnNode->addComponent(rightBox);
    this->addChild(rightColumnNode);
}

void GameScene::updatePlayer(float dt) {

    if (_player) {
        for (auto i : listOfBlocks)
        {
            if (_player && _player->getPosition().y > i->getPosition().y && _player->getPosition().y <= i->getPosition().y + i->getContentSize().height) {
                if (_player && _player->getPositionX() > i->getPositionX() || _player->getPositionX() < i->getPositionX() + i->getContentSize().width) {
                    auto collisionRect = i->getBoundingBox();
                    collisionRect.size.width = i->getContentSize().width * 0.48;
                    collisionRect.size.height = i->getContentSize().height * 0.48;
     
                    if (_player && collisionRect.containsPoint(_player->getPosition() + (_player->getDirection() * (130 + (_player->getMovementLevel() / 3)) * dt)
                        + (_player->getDirection().x > 0 ? Vec2(i->getContentSize().width / 7, 0) : Vec2(-i->getContentSize().width / 7, 0)))) {
                        _player->getPhysicsBody()->setVelocity(Vec2(0, _player->getPhysicsBody()->getVelocity().y));
                        _player->setIsCanMove(false);
                        _player->setPositionX(_player->getPositionX() - (_player->getDirection().x/10));
                    }
                }
              
            }
        }

        if (lifeSpawn && lifeSpawn->getBoundingBox().containsPoint(_player->getPosition())) {
            audioEngine->playSFX("Sounds/clickCommodity.mp3");
            auto animCoin = Sprite::create("animation/spark/spark (1).png");
            animCoin->setPosition(lifeSpawn->getPosition());
            Utilities::loadSpriteFrameCache("animation/", "spark");
            auto aniMove = Utilities::createAnimation("spark", 99, 0.1f);
            Animate* animate_Move = Animate::create(aniMove);
            animCoin->runAction(animate_Move);
            this->addChild(animCoin, 5);
            lifeSpawn->removeFromParentAndCleanup(true); lifeSpawn = nullptr;
            _player->spawnLife();
        }

        //
        Vec2 playerPosition = _player->getPosition();
        Size playerSize = _player->getContentSize();
        auto minPosX = columnWidth/2;
        auto maxPosX = visibleSize.width-minPosX;

        _player->setDirection(_joystick->getDirection());
        if (_player && playerPosition.x > maxPosX - 17) {
            _player->getPhysicsBody()->setVelocity(Vec2(0, _player->getPhysicsBody()->getVelocity().y));
            _player->setIsCanMove(false);
            _player->setPositionX(maxPosX - 16);
            collisionWall = true;
            checkRun = 1;
        }

         else if(_player && playerPosition.x < minPosX+17) {

            // Kiểm tra va chạm với từng cột riêng lẻ
           
                 _player->getPhysicsBody()->setVelocity(Vec2(0, _player->getPhysicsBody()->getVelocity().y));
                _player->setIsCanMove(false);
            _player->setPositionX(minPosX + 16);
                collisionWall = true;
                checkRun = -1;
        }
        if ( _player->getDirection().x!=checkRun && collisionWall==true)
        {
            checkRun = 0;
            _player->setIsCanMove(true);                        
            collisionWall = false;
        }
        // 
        // 
        // update player move and jump action
        float s = visibleSize.width - (columnWidth / 2);
        _player->update(dt, columnWidth / 2, s);
        x2coin->setString(std::to_string(_player->getCoinAmount()));
        textShield->setString(std::to_string(_player->getShieldAmount()));
        x2jump->setString(std::to_string(_player->getJumpAmount()));

        // update jump action
        if (_jumpButton) {
            if (_jumpButton->getIsPress()) {
                _player->setJump(true);
                _player->increaseJumpCount();
                _jumpButton->resetPressed();
            }
        }
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

        if (std::to_string(_player->getSpawnLife()) != lifeLabel->getString()) {
            lifeLabel->setString(std::to_string(_player->getSpawnLife()));
        }

        if (_player->getX2Coin()) {
            if (_player->getX2Coin()->getSkillCooldown() >= 0) {
                _player->getX2Coin()->setSkillCooldown(_player->getX2Coin()->getSkillCooldown() - dt);
            }
            else
            {
                    if (skillSpriteCoin!=nullptr)
                    {
                    skillSpriteCoin->setVisible(false);
                    }
            }
        }
       
            if (disableSpriteCoin != nullptr)
            {
                if (_player->getCoinAmount()<1)
                {
                disableSpriteCoin->setVisible(true);
                }
                else
                {
                disableSpriteCoin->setVisible(false);
                }
            }
        

        if (_player->getX2Jump()) {
            if (_player->getX2Jump()->getSkillCooldown() >= 0) {
                _player->getX2Jump()->setSkillCooldown(_player->getX2Jump()->getSkillCooldown() - dt);
            }
            else
            {
                    if (skillSpriteJump != nullptr)
                    {
                        skillSpriteJump->setVisible(false);
                    }

            }
        }
            if (disableSpriteJump != nullptr)
            {
                if (_player->getJumpAmount()<1)
                {

                disableSpriteJump->setVisible(true);
                }
                else
                {
                disableSpriteJump->setVisible(false);

                }
            }
        if (_player->getShield()) {
            if (_player->getShield()->getSkillCooldown() >= 0) {
                _player->getShield()->setSkillCooldown(_player->getShield()->getSkillCooldown() - dt);
            }
            else
            {

                    if (skillSpriteShield != nullptr)
                    {
                        skillSpriteShield->setVisible(false);
                    }
            }
        }
           if (disableSpriteShield != nullptr)
            {
               if (_player->getShieldAmount()<1)
               {

                disableSpriteShield->setVisible(true);
               }
               else
               {
                disableSpriteShield->setVisible(false);

               }
            }


        // contact with coin
        if (!listOfCoins.empty()) {
            std::vector<Coin*> listRemoveCoin;
            for (auto c : listOfCoins) {
                if (c->getBoundingBox().containsPoint(_player->getPosition())) {
                    audioEngine->playSFX("Sounds/clickCommodity.mp3");
            auto animCoin = Sprite::create("animation/spark/spark (1).png");
            animCoin->setPosition(c->getPosition());
            Utilities::loadSpriteFrameCache("animation/", "spark");
            auto aniMove = Utilities::createAnimation("spark", 99, 0.1f);
            Animate* animate_Move = Animate::create(aniMove);
            animCoin->runAction(animate_Move);
            this->addChild(animCoin, 5);
            
                    c->removeFromParentAndCleanup(true);
                    listRemoveCoin.push_back(c);
                    if (!_player->isX2Coin()) {
                        CoinManager::getInstance()->increaseCoins(1);
                        _player->increaseMoney(1);
                        coin->setString(std::to_string(_player->getMoney()));
                    }
                    else {

                        CoinManager::getInstance()->increaseCoins(2);
                        _player->increaseMoney(2);
                        coin->setString(std::to_string(_player->getMoney()));
                    }
                }
            }
            for (auto coin : listRemoveCoin) {
                auto it = std::find(listOfCoins.begin(), listOfCoins.end(), coin);
                if (it != listOfCoins.end()) {
                    listOfCoins.erase(it);
                }
            }
        }

     
        for (auto bl : listOfBlocks)
        {
            Rect plrRect(_player->getPosition() + (_player->getPhysicsBody()->getVelocity() * dt) - Vec2(70, 30), Size(90, 50));
            if (plrRect.containsPoint(bl->getPosition())) {
                _player->setIsCanMove(false);
            }
            else {
                _player->setIsCanMove(true);
            }
        }

        Rect plrRect(_player->getPosition() + (_player->getPhysicsBody()->getVelocity() * dt) - Vec2(70, 30), Size(90, 50));
        /*if (plrRect.containsPoint(lifeSpawn->getPosition())) {
            lifeSpawn->removeFromParentAndCleanup(true);
            lifeSpawn = nullptr;
            _player->spawnLife();
        }
        else {
            lifeSpawn->removeFromParentAndCleanup(true);
            lifeSpawn = nullptr;
            _player->spawnLife();
        }*/

      /*  Rect leftRect(leftColumnNode->getPosition(), leftColumnNode->getContentSize());
        if (leftRect.containsPoint(_player->getPosition() + (_player->getPhysicsBody()->getVelocity() * dt))) {
            _player->setIsCanMove(false);
        }
        else {
            _player->setIsCanMove(true);
        }

        Rect rightRect(rightColumnNode->getPosition(), rightColumnNode->getContentSize());
        if (rightRect.containsPoint(_player->getPosition() + (_player->getPhysicsBody()->getVelocity() * dt))) {
            _player->setIsCanMove(false);
        }
        else {
            _player->setIsCanMove(true);
        }*/
    }
}
void GameScene::updateCoin(float dt) {
    if (_player->isX2Coin()) {
        for (auto c : listOfCoins)
        {
            if (!c->isDouble())
                c->setCoinDouble();
        }
    }
    else {
        for (auto c : listOfCoins)
        {
            if (c->isDouble())
                c->setCoinNormal();
        }
    }
}

void GameScene::onExit()
{
    // Gọi phương thức onExit() của lớp cha
    Scene::onExit();
}
