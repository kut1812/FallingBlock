#include "cocostudio/CocoStudio.h"
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
    visibleSize = Director::getInstance()->getVisibleSize();

    _player = _plr;
    _player->setPosition(Vec2(visibleSize.width / 2, 2));
    _player->setTag(909);
    this->addChild(_player, 1);

    this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    this->getPhysicsWorld()->setGravity(Vec2(0, -980));

    auto uiMenu = CSLoader::getInstance()->createNode("csb/Layer.csb");
    this->addChild(uiMenu);

    auto column = uiMenu->getChildByName<Sprite*>("block_16_0");
    columnWidth = column->getContentSize().width;

    auto uiButton = CSLoader::getInstance()->createNode("csb/ButtonGameScene.csb");
    this->addChild(uiButton, 1);

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
            if (_player->getX2Coin() && _player->getCoinAmount() > 0) {
            _player->getX2Coin()->use();
            _player->decreaseCoinAmount(1);
            dbManager->setPlayerInfo(1, _player->getMovementLevel(), _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), _player->getCoinAmount(), _player->getJumpAmount(), _player->getShieldAmount());
            skillSpriteCoin = Sprite::create("control/fb_ctrl_skill_dup_coin_wait.png");
            skillSpriteCoin->setPosition(Vec2(visibleSize.width * 0.77, visibleSize.height * 0.15));
            skillSpriteCoin->setScale(0.5);
            Director::getInstance()->getRunningScene()->addChild(skillSpriteCoin, 3);

            auto label = Label::createWithTTF(StringUtils::format("%.1f", 20.0f), "font/Baloo2/Baloo2-Bold.ttf", 24);
            label->setPosition(skillSpriteCoin->getPosition());
            Director::getInstance()->getRunningScene()->addChild(label, 3);

            float remainingCooldown = 20.0f;

            Director::getInstance()->getScheduler()->schedule([=](float dt) mutable {
                remainingCooldown -= dt;
                label->setString(StringUtils::format("%.1f", remainingCooldown));

                if (remainingCooldown <= 0) {
                    label->removeFromParent();
                }
                }, label, 0.1f, kRepeatForever, 0.0f, false, "cooldown_scheduler1");
            }
        }
        });
    if (!_player->getX2Coin()) coinDouble->setVisible(false);
    //button shield
    auto shield = uiButton->getChildByName<ui::Button*>("Button_5");
    shield->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (_player->getShield() && _player->getShieldAmount() > 0) {
                _player->getShield()->use();
                _player->decreaseShieldAmount(1);
                dbManager->setPlayerInfo(1, _player->getMovementLevel(), _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), _player->getCoinAmount(), _player->getJumpAmount(), _player->getShieldAmount());
                skillSpriteShield = Sprite::create("control/fb_ctrl_skill_dup_coin_wait.png");
                skillSpriteShield->setPosition(Vec2(visibleSize.width * 0.79, visibleSize.height * 0.27));
                skillSpriteShield->setScale(0.5);

                Director::getInstance()->getRunningScene()->addChild(skillSpriteShield, 3);

                auto label = Label::createWithTTF(StringUtils::format("%.1f", 10.0f), "font/Baloo2/Baloo2-Bold.ttf", 24);
                label->setPosition(skillSpriteShield->getPosition());
                Director::getInstance()->getRunningScene()->addChild(label, 3);

                float remainingCooldown = 10.0f;

                Director::getInstance()->getScheduler()->schedule([=](float dt) mutable {
                    remainingCooldown -= dt;
                    label->setString(StringUtils::format("%.1f", remainingCooldown));

                    if (remainingCooldown <= 0) {
                        label->removeFromParent();
                    }
                    }, label, 0.1f, kRepeatForever, 0.0f, false, "cooldown_scheduler2");
            }

        }
        });
    if (!_player->getShield()) shield->setVisible(false);
    //button doubleJump
    auto doubleJump = uiButton->getChildByName<ui::Button*>("Button_6");
    doubleJump->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (_player->getX2Jump() && _player->getJumpAmount() > 0) {
                _player->getX2Jump()->use();
                _player->decreaseJumpAmount(1);
                dbManager->setPlayerInfo(1, _player->getMovementLevel(), _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), _player->getCoinAmount(), _player->getJumpAmount(), _player->getShieldAmount());
                skillSpriteJump = Sprite::create("control/fb_ctrl_skill_dup_coin_wait.png");
                skillSpriteJump->setPosition(Vec2(visibleSize.width * 0.85, visibleSize.height * 0.32));
                skillSpriteJump->setScale(0.5);
                Director::getInstance()->getRunningScene()->addChild(skillSpriteJump, 3);

                auto label = Label::createWithTTF(StringUtils::format("%.1f", 10.0f), "font/Baloo2/Baloo2-Bold.ttf", 24);
                label->setPosition(skillSpriteJump->getPosition());
                Director::getInstance()->getRunningScene()->addChild(label, 3);

                float remainingCooldown = 10.0f;

                Director::getInstance()->getScheduler()->schedule([=](float dt) mutable {
                    remainingCooldown -= dt;
                    label->setString(StringUtils::format("%.1f", remainingCooldown));

                    if (remainingCooldown <= 0) {
                        label->removeFromParent();
                    }
                    }, label, 0.1f, kRepeatForever, 0.0f, false, "cooldown_scheduler3");
            }
        }
        });
    if (!_player->getX2Jump()) doubleJump->setVisible(false);
    //button upgrade
    auto upgrade = uiButton->getChildByName<ui::Button*>("Button_1");
    upgrade->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto upgradeLayer = UpgradeLayer::create(_player);
            this->addChild(upgradeLayer,3);
        }
        });
    //button shop
    auto shop = uiButton->getChildByName<ui::Button*>("Button_2");
    shop->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto storeLayer = StoreLayer::create(_player);
            this->addChild(storeLayer,4);
        }
        });
    //label life
    lifeLabel = Label::createWithTTF(std::to_string(_player->getSpawnLife()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    lifeLabel->setPosition(Vec2(visibleSize.width*0.24,visibleSize.height*0.92));
    this->addChild(lifeLabel,1);    
    //label coin
    coin = Label::createWithTTF(std::to_string(CoinManager::getInstance()->getCoin()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    coin->setPosition(Vec2(visibleSize.width * 0.44, visibleSize.height * 0.92));
    this->addChild(coin, 1);
    //label x2jump
    x2jump = Label::createWithTTF(std::to_string(_player->getJumpAmount()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    x2jump->setPosition(Vec2(visibleSize.width * 0.53, visibleSize.height * 0.92));
    this->addChild(x2jump, 1);
    //label shield
    textShield = Label::createWithTTF(std::to_string(_player->getShieldAmount()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    textShield->setPosition(Vec2(visibleSize.width * 0.6, visibleSize.height * 0.92));
    this->addChild(textShield, 1);
    //label x2coin
    x2coin = Label::createWithTTF(std::to_string(_player->getCoinAmount()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    x2coin->setPosition(Vec2(visibleSize.width * 0.67, visibleSize.height * 0.92));
    this->addChild(x2coin, 1);

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
    _joystick->setPosition(visibleSize.width / 8, visibleSize.height * 0.15);

    _jumpButton = JumpButton::create();
    if (_jumpButton) {
        this->addChild(_jumpButton, 1);
    }
    _jumpButton->setPosition(visibleSize.width * 0.85, visibleSize.height * 0.15);

    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::updatePlayer), 0.1f);
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
        auto spawnX = columnWidth / 2 + block->getContentSize().width / 2 * randomNum;
        blockSize = Size(block->getContentSize());
        block->setPosX(spawnX);
        block->setAnchorPoint(Vec2(0, 0));
        block->setPosition(Vec2(spawnX, visibleSize.height / 1.3));
        this->addChild(block);
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
        coin->setScale(1.4);
        auto randomX = Utilities::getInstance()->generateNumber(0, 13);
        auto randomY = Utilities::getInstance()->generateNumber(2, 8);
        auto spawnX = columnWidth / 2 + coin->getContentSize().width / 2 * randomX;
        float a = randomY;
        int posY = a / 10 * visibleSize.height;
        CCLOG("%d", posY);
        coin->setPosition(Vec2(spawnX,posY));
        coin->setAnchorPoint(Vec2(0, 0));
        this->addChild(coin,3);
        listOfCoins.push_back(coin);
        }
    }
}

void GameScene::setDynamicAllBlock(int x)
{
    for (auto i : listOfBlocks) {
        if (i != nullptr)
        {
            i->getPhysicsBody()->setVelocity(Vec2(i->getPhysicsBody()->getVelocity().x,x));
        }
    }
}

void GameScene::updateMeter(float dt) {
    if (_player) {
        currentMeter = savedMeterBe4Reset + _player->getPositionY() / 10;
        float myFloat = std::atof(mileageCounter->getString().c_str());
        if (currentMeter - 2 > myFloat)
        {
            mileageCounter->setMileage(currentMeter - 1);
        }
        if (currentMeter > limitMeter && _player->getPositionY() <= (visibleSize.height - (visibleSize.height / 5)) && _player->getPhysicsBody()->getVelocity().y >= -0.1 && _player->getPhysicsBody()->getVelocity().y <= 0.1) {
            std::vector<Block*> listToRemove;
            int count = 0;
            for (auto i : listOfBlocks) {
                if (i->getPositionY() <= i->getSpriteSize().height && i->getPositionY() >= 0 && count <= 14) {
                    i->setFlop();
                    listToRemove.push_back(i);
                    count++;
                }
            }
            limitMeter += 20;
            savedMeterBe4Reset = currentMeter - ((currentMeter - limitMeter) > currentMeter ? (currentMeter - limitMeter) : 0);
        }
    }
}

bool GameScene::OnContactBegan(cocos2d::PhysicsContact& contact)
{
    auto bodyA = contact.getShapeA()->getBody()->getNode();
    auto bodyB = contact.getShapeB()->getBody()->getNode();

    if (bodyA && bodyB) {
        if (bodyA->getPhysicsBody() && bodyB->getPhysicsBody() && bodyA->getPhysicsBody()->getCollisionBitmask() == 30 && bodyB->getPhysicsBody()->getCollisionBitmask() == 11 ||
            bodyA->getPhysicsBody() && bodyB->getPhysicsBody() && bodyA->getPhysicsBody()->getCollisionBitmask() == 11 && bodyB->getPhysicsBody()->getCollisionBitmask() == 30
            )
        {
            if(_player->getSpawnLife() <= 0) {
                this->setDynamicAllBlock(200);
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
                auto score = MileageCounter::create("font/Baloo2/Baloo2-Bold.ttf", mileageCounter->getString(), 20);
                auto loseLayer = LayerManager::getInstance()->loseLayer(std::stoi(mileageCounter->getString()));
                this->addChild(loseLayer, 4);
                loseLayer->addChild(score, 0);
                score->setPosition(Vec2(visibleSize.width * 0.51, visibleSize.height * 0.5));
            }
            else {
                _player->decreaseSpawnLife();
                if (bodyA->getPhysicsBody()->getCollisionBitmask() == 30) {
                    bodyA->getPhysicsBody()->removeFromWorld();
                    bodyA->setVisible(false);
                }
                else if (bodyB->getPhysicsBody()->getCollisionBitmask() == 30) {
                    bodyB->getPhysicsBody()->removeFromWorld();
                    bodyB->setVisible(false);
                }
            }
        }
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

    leftColumnNode = Node::create();
    leftColumnNode->setPosition(Vec2(0, visibleSize.height / 2));
    auto leftBox = PhysicsBody::createBox(Size(columnWidth, visibleSize.height));
    leftBox->setDynamic(false);
    leftBox->setCategoryBitmask(15);
    leftBox->setCollisionBitmask(15);
    leftBox->setContactTestBitmask(true);
    leftColumnNode->addComponent(leftBox);
    this->addChild(leftColumnNode);

    rightColumnNode = Node::create();
    rightColumnNode->setPosition(Vec2(visibleSize.width, visibleSize.height / 2));
    auto rightBox = PhysicsBody::createBox(Size(columnWidth, visibleSize.height));
    rightBox->setDynamic(false);
    rightBox->setCategoryBitmask(15);
    rightBox->setCollisionBitmask(15);
    rightBox->setContactTestBitmask(true);
    rightColumnNode->addComponent(rightBox);
    this->addChild(rightColumnNode);
}

void GameScene::updatePlayer(float dt) {

    if (_player) {

        // update player move and jump action
        _player->setDirection(_joystick->getDirection());
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
            for (auto coin : listOfCoins) {
                if (coin->getBoundingBox().containsPoint(_player->getPosition())) {
                    coin->removeFromParentAndCleanup(true);
                    listRemoveCoin.push_back(coin);
                    if (!_player->isX2Coin())
                        CoinManager::getInstance()->increaseCoins(1);
                    else
                        CoinManager::getInstance()->increaseCoins(2);
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

        Rect leftRect(leftColumnNode->getPosition(), leftColumnNode->getContentSize());
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
        }
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