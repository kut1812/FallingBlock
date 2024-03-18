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
    Utilities::getInstance()->loadSpriteFrameCache("animation/", "skull_relax");
    auto idleAnimation = Utilities::createAnimation("skull_relax", 20, 0.2f);
    auto walkAnimation = Utilities::createAnimation("skull_move", 20, 0.2f);
    AnimationCache::getInstance()->addAnimation(idleAnimation, "IDLE_ANIM");
    AnimationCache::getInstance()->addAnimation(walkAnimation, "MOVE_ANIM");
    characterSprite = Sprite::create("object/fb_object_skull.png");
    characterSprite->runAction(RepeatForever::create(Animate::create(idleAnimation)));
    this->addChild(characterSprite);
    return true;
}

void Player::update(float dt) {

}

void Player::changeState(PlayerState newState) {
    /*if (currentState)
        currentState->exit();

    switch (newState) {
    case PlayerState::IDLE:
        currentState = idleState;
        break;
    case PlayerState::MOVE_LEFT:
        currentState = moveLeftState;
        break;
    case PlayerState::MOVE_RIGHT:
        currentState = moveRightState;
        break;
    case PlayerState::JUMPING:
        currentState = jumpingState;
        break;
    }

    currentState->enter();*/

}