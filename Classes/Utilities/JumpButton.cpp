#include "cocos2d.h"
#include "AudioEngine/AudioEngine.h"
USING_NS_CC;
class JumpButton : public cocos2d::Node
{
public:
    JumpButton();

    virtual bool init();

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    void onKeyDown(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyUp(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    bool getIsPress() const { return isPressed; };
    void resetPressed() { isPressed = false; };
    CREATE_FUNC(JumpButton);

private:
    Audio* audioEngine;
    bool isPressed = false;
    Sprite* btnSprite;
};

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

    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(JumpButton::onKeyDown, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(JumpButton::onKeyUp, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

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

void JumpButton::onKeyDown(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        // Xử lý khi bấm phím space
        isPressed = true;
    }
}

void JumpButton::onKeyUp(EventKeyboard::KeyCode keyCode, Event* event)
{
    if (keyCode == EventKeyboard::KeyCode::KEY_SPACE)
    {
        // Xử lý khi nhả phím space
        isPressed = false;
    }
}
