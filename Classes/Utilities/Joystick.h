#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "cocos2d.h"
#include "AudioEngine/AudioEngine.h"
USING_NS_CC;
class Joystick : public cocos2d::Node
{
public:
    Joystick();

    // Khởi tạo joystick
    virtual bool init();

    // Phương thức xử lý sự kiện chạm
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    // Trả về hướng của joystick
    Vec2 getDirection();
    bool getIsPress() const { return isPressed; };
    CREATE_FUNC(Joystick);

private:
    Audio* audioEngine;
    bool isPressed;
    Sprite* joystickBorder;
    Sprite* joystickBtn;
    Vec2 prevPosBeforeRelease = Vec2::ZERO;
    Vec2 centerPos;
    Vec2 originalPosition;
    Vec2 currentDirection;
};

#endif // __JOYSTICK_H__