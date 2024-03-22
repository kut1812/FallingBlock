#ifndef __JUMP_BUTTON__
#define __JUMP_BUTTON__

#include "cocos2d.h"
USING_NS_CC;
class JumpButton : public cocos2d::Node
{
public:
    JumpButton();

    virtual bool init();

    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    bool getIsPress() const { return isPressed; };
    CREATE_FUNC(JumpButton);

private:
    bool isPressed;
    Sprite* btnSprite;
};

#endif // __JUMP_BUTTON__