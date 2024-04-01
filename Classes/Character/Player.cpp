#include "Player.h"
#include "../Utilities/Utilities.h"
#include "WorkingWithData/SQLiteManager.h"
Player* Player::createPlayer() {
    Player* player = new (std::nothrow) Player();
    if (player && player->init()) {
        player->autorelease();
        return player;
    }
    else {
        delete player;
        player = nullptr;
        return nullptr;
    }
}

bool Player::init() {
    if (!Node::init()) {
        return false;
    }
    SQLiteManager* dbManager = SQLiteManager::getInstance();
    SQLiteManager::PlayerInfo playerInfo = dbManager->getPlayerById(1);
    this->movementLevel = playerInfo.movement_speed;
    this->money = playerInfo.money;
    this->blockSpeedLv = playerInfo.block_speed;
    this->lifeSpawnLevel = playerInfo.life_spawn;
    this->skillDurationLevel = playerInfo.skill_duration;
    this->movementSpeed = 140 + (movementLevel / 3);
    this->currentLifeSpawnTime = 320.0f - this->lifeSpawnLevel / 3;
    this->jumpAmount = playerInfo.x2JumpActive;
    this->coinAmount = playerInfo.x2CoinActive;
    this->shieldAmount = playerInfo.shieldActive;
    this->retain();
    Utilities::getInstance()->loadSpriteFrameCache("animation/", "block_falled");
    auto sfx_block_falled = Utilities::createAnimation("block_falled", 19, 0.2f);
    Utilities::getInstance()->loadSpriteFrameCache("animation/", "skull_relax");
    Utilities::getInstance()->loadSpriteFrameCache("animation/", "shield");
    Utilities::getInstance()->loadSpriteFrameCache("animation/", "wing");

    AnimationCache::getInstance()->addAnimation(sfx_block_falled, "block_falled");
    auto walkAnimation = Utilities::createAnimation("skull_relax", 20, 0.2f);
    auto idleAnimation = Utilities::createAnimation("skull_move", 20, 0.1f);
    auto shieldAnimation = Utilities::createAnimationPng("skill_sheild", 20, 0.1f);
    auto wingAnimation = Utilities::createAnimationPng("double_jump", 20, 0.1f);
    characterSprite = Sprite::createWithSpriteFrameName("skull_relax (1)");

    AnimationCache::getInstance()->addAnimation(idleAnimation, "IDLE_ANIM");
    AnimationCache::getInstance()->addAnimation(walkAnimation, "MOVE_ANIM");

    characterSprite->runAction(RepeatForever::create(Animate::create(idleAnimation)));
    characterSprite->retain();
    this->addChild(characterSprite);

    wingSprite = Sprite::createWithSpriteFrameName("double_jump (1).png");
    wingSprite->runAction(RepeatForever::create(Animate::create(wingAnimation)));
    characterSprite->addChild(wingSprite);

    wingSprite->setPosition(Vec2(0, characterSprite->getContentSize().height * 0.9));
    wingSprite->setScale(0.4);
    wingSprite->retain();
    wingSprite->setVisible(false);

    shieldSprite = Sprite::createWithSpriteFrameName("skill_sheild (1).png");
    shieldSprite->runAction(RepeatForever::create(Animate::create(shieldAnimation)));
    shieldSprite->setScale(0.4);
    shieldSprite->setPosition(Vec2(0, 28));
    shieldSprite->setVisible(false);
    shieldSprite->retain();
    this->addChild(shieldSprite);

    auto physicsBody = PhysicsBody::createBox(characterSprite->getContentSize(), PhysicsMaterial(1.0f, 0.1f, 1.0f));
    physicsBody->setDynamic(true);
    physicsBody->setMass(1);
    physicsBody->setRotationEnable(false);
    physicsBody->setContactTestBitmask(true);
    physicsBody->setCollisionBitmask(10);
    this->addComponent(physicsBody);

    playerHead = Node::create();
    playerHead->setContentSize(characterSprite->getContentSize() - Size(20, 30));
    playerHead->setPosition(Vec2(this->getPositionX() - 13, this->getPositionY() + 20));
    auto physicsHead = PhysicsBody::createBox(playerHead->getContentSize());
    physicsHead->setDynamic(false);
    physicsHead->setContactTestBitmask(true);
    physicsHead->setCollisionBitmask(11);
    playerHead->addComponent(physicsHead);
    this->addChild(playerHead);

    this->idleState = new IdleState(this);
    this->idleLeftState = new IdleLeftState(this);
    this->moveLeftState = new MoveLeftState(this);
    this->moveRightState = new MoveRightState(this);

    this->x2JumpSkill = new X2JumpSkill(this, 20.0f - skillDurationLevel / 40);
    this->x2JumpSkill->init();
    CCLOG("%d this->skillDurationLevel", this->skillDurationLevel);
    CCLOG("%f this->x2JumpSkill->getSkillCooldown() - skillDurationLevel / 40", this->x2JumpSkill->getMaxSkillCooldown() - skillDurationLevel / 40);
    this->x2CoinSkill = new X2CoinSkill(this, 20.0f - skillDurationLevel / 40);
    this->x2CoinSkill->init();
    this->shieldSkill = new ShieldSkill(this, 25.0f - skillDurationLevel / 40);
    this->shieldSkill->init();

    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->schedule(CC_SCHEDULE_SELECTOR(Player::spawnLife), currentLifeSpawnTime, CC_REPEAT_FOREVER, 0.0f);

    return true;
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_Q:
        break;
    }
}

void Player::spawnLife(float dt) {
    currentSpawnLife++;
}

void Player::update(float dt, float leftBorder, float rightBorder) {
    // handle move physicsBody by velocity
   
    if (_isCanMove) {
        this->getPhysicsBody()->setVelocity(Vec2((direction * movementSpeed).x, this->getPhysicsBody()->getVelocity().y));
        playerHead->setPosition(Vec2(-5, 25));
    }
    else {
        this->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }

    // impulse physicsBody to jump
    if (jumpCount > 0 && jumpCount <= maxJumpCount && isJumping) {
        this->getPhysicsBody()->applyImpulse(Vec2(0, 360));
        playerHead->setPosition(Vec2(-5, 25));
        isJumping = false;
    }
    
    // handle 
    Vec2 currentVelocity = this->getPhysicsBody()->getVelocity();
    if (currentVelocity.y <= 0.5) {
        if(currentVelocity.y > -0.5)
            jumpCount = 0;
        this->getPhysicsBody()->setVelocity(Vec2(currentVelocity.x, currentVelocity.y));
    }
    prevDirection = direction;
}

void Player::changeState(PlayerState newState) {
    if (currentState != nullptr)
        currentState->exit();

    switch (newState) {
    case PlayerState::IDLE:
        currentState = idleState;
    case PlayerState::IDLE_LEFT:
        currentState = idleLeftState;
        break;
    case PlayerState::MOVE_LEFT:
        currentState = moveLeftState;
        break;
    case PlayerState::MOVE_RIGHT:
        currentState = moveRightState;
        break;
    }

    if (currentState != nullptr)
        currentState->enter();
}


void Player::setSkillDurationLevel(int lv) { 
    skillDurationLevel = lv;
    this->x2JumpSkill->setMaxSkillCooldown(20.0f - lv / 40);
    this->x2CoinSkill->setMaxSkillCooldown(20.0f - lv / 40);
    this->shieldSkill->setMaxSkillCooldown(25.0f - lv / 40);
}

void Player::setLifeSpawnLevel(int lv) { 
    lifeSpawnLevel = lv; 
    currentLifeSpawnTime = 320.0f - lifeSpawnLevel / 8;
}
void Player::setMovementLevel(int lv) { 
    movementLevel = lv;
    this->movementSpeed = 140 + (movementLevel / 3);
}

Player::~Player() {
}