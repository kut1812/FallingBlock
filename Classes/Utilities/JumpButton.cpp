#include "./JumpButton.h"

USING_NS_CC;

JumpButton::JumpButton() : isPressed(false)
{
}

bool JumpButton::init()
{
    if (!Node::init()) // Thay đổi đường dẫn hình ảnh joystick của bạn
    {
        return false;
    }
    btnSprite = Sprite::create("control/fb_ctrl_jump.png");
    btnSprite->setPosition(Vec2());
    btnSprite->setScale(0.5);
    this->addChild(btnSprite, 500);

    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(JumpButton::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(JumpButton::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(JumpButton::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

    return true;
}

bool JumpButton::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 touchLocationInNode = this->convertToNodeSpace(touch->getLocation());

    if (btnSprite->getBoundingBox().containsPoint(touchLocationInNode))
    {
        isPressed = false;
        return true;
    }
    return false;
}

void JumpButton::onTouchMoved(Touch* touch, Event* event)
{
}

void JumpButton::onTouchEnded(Touch* touch, Event* event)
{
    Vec2 touchLocationInNode = this->convertToNodeSpace(touch->getLocation());

    if (btnSprite->getBoundingBox().containsPoint(touchLocationInNode))
    {
        isPressed = true;
    }
}