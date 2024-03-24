#include "Player.h"
#include "../Utilities/Utilities.h"
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
    Utilities::getInstance()->loadSpriteFrameCache("animation/", "block_falled");
    auto sfx_block_falled = Utilities::createAnimation("block_falled", 19, 0.2f);
    AnimationCache::getInstance()->addAnimation(sfx_block_falled, "block_falled");

    Utilities::getInstance()->loadSpriteFrameCache("animation/", "skull_relax");
    auto walkAnimation = Utilities::createAnimation("skull_relax", 20, 0.2f);
    auto idleAnimation = Utilities::createAnimation("skull_move", 20, 0.1f);
    auto wingAnimation = Utilities::createAnimationPng("double_jump", 20, 0.1f);
    AnimationCache::getInstance()->addAnimation(idleAnimation, "IDLE_ANIM");
    AnimationCache::getInstance()->addAnimation(walkAnimation, "MOVE_ANIM");
    Utilities::getInstance()->loadSpriteFrameCache("animation/", "wing");
    characterSprite = Sprite::createWithSpriteFrameName("skull_relax (1)");
    characterSprite->runAction(RepeatForever::create(Animate::create(idleAnimation)));
    this->addChild(characterSprite);


    //Sprite::createWithSpriteFrameName("fighter_armed_idle_E_0.0_0.png");
    wingSprite = Sprite::createWithSpriteFrameName("double_jump (1).png");
    wingSprite->runAction(RepeatForever::create(Animate::create(wingAnimation)));
    characterSprite->addChild(wingSprite);
    wingSprite->setPosition(Vec2(0, characterSprite->getContentSize().height * 0.9));
    wingSprite->setScale(0.4);
    wingSprite->setVisible(false);


    auto physicsBody = PhysicsBody::createBox(characterSprite->getContentSize(), PhysicsMaterial(1.0f, 0.1f, 1.0f));
    physicsBody->setDynamic(true);
    physicsBody->setMass(1);
    physicsBody->setRotationEnable(false);
    physicsBody->setCollisionBitmask(10);
    physicsBody->setContactTestBitmask(true);
    this->addComponent(physicsBody);
    this->idleState = new IdleState(this);
    this->idleLeftState = new IdleLeftState(this);
    this->moveLeftState = new MoveLeftState(this);
    this->moveRightState = new MoveRightState(this);
    this->x2JumpSkill = new X2JumpSkill(this);
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(Player::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);


    return true;
}

void Player::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_Q:
        CCLOG("press q");
        this->x2JumpSkill->use();
        break;
        // Thêm các xử lí cho các phím khác ở đây
    }
}


void Player::update(float dt, float leftBorder, float rightBorder) {
    // handle move physicsBody by velocity
    this->getPhysicsBody()->setVelocity(Vec2((direction * movementSpeed).x, this->getPhysicsBody()->getVelocity().y));

    // impulse physicsBody to jump
    if (jumpCount > 0 && jumpCount <= maxJumpCount && isJumping) {
        this->getPhysicsBody()->applyImpulse(Vec2(0, 360));
        isJumping = false;
    }
    
    // handle 
    Vec2 currentVelocity = this->getPhysicsBody()->getVelocity();
    if (currentVelocity.y <= 0.5) {
        if(currentVelocity.y > -0.5)
            jumpCount = 0;
        this->getPhysicsBody()->setVelocity(Vec2(currentVelocity.x, currentVelocity.y));
    }

}

void Player::changeState(PlayerState newState) {
    if (currentState)
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

    currentState->enter();

}