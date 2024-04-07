#include "Joystick.h"
USING_NS_CC;

Joystick::Joystick() : isPressed(false), currentDirection(Vec2::ZERO)
{
}

bool Joystick::init()
{
    if (!Node::init()) // Thay đổi đường dẫn hình ảnh joystick của bạn
    {
        return false;
    }

    audioEngine = Audio::getInstance();

    joystickBorder = Sprite::create("control/fb_ctrl_pad.png");
    joystickBorder->setPosition(Vec2());
    joystickBorder->setScale(0.5);
    this->addChild(joystickBorder, 300);

    joystickBtn = Sprite::create("control/fb_ctrl_move.png");
    joystickBtn->setPosition(Vec2());
    joystickBtn->setScale(0.5);
    this->addChild(joystickBtn, 500);
    centerPos = joystickBtn->getPosition();

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(Joystick::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Joystick::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Joystick::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

bool Joystick::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 touchLocationInNode = this->convertToNodeSpace(touch->getLocation());
    if (joystickBtn->getBoundingBox().containsPoint(touchLocationInNode))
    {
        if (audioEngine->getPressJoystickSoundId() == 0) {
            audioEngine->setPressJoystickSoundId(audioEngine->play2d("Sounds/click.mp3", true));
        }
        else {
            audioEngine->resume(audioEngine->getPressJoystickSoundId());
        }
        isPressed = true;
        return true;
    }
    return false;
}

void Joystick::onTouchMoved(Touch* touch, Event* event)
{
    if (isPressed)
    {
        Vec2 touchLocationInNode = this->convertToNodeSpace(touch->getLocation());
        Vec2 direction = touchLocationInNode - centerPos;
        float distance = direction.length();

        float radius = joystickBorder->getContentSize().width / 2;

        if (distance > radius)
        {
            direction.normalize();
            direction *= radius;
            joystickBtn->setPosition(Vec2((centerPos + direction).x, joystickBtn->getPositionY()));
        }
        else
        {
            joystickBtn->setPosition(Vec2(touchLocationInNode.x, joystickBtn->getPositionY()));
        }
    }
}

void Joystick::onTouchEnded(Touch* touch, Event* event)
{
    audioEngine->pause(audioEngine->getPressJoystickSoundId());
    prevPosBeforeRelease = joystickBtn->getPosition();
    joystickBtn->setPosition(centerPos);
    isPressed = false;
}

Vec2 Joystick::getDirection()
{
    if (isPressed) {
        auto result = joystickBtn->getPosition() - centerPos;
        result.normalize();
        return result;
    }
    else
    {
        return Vec2::ZERO;
    }
}