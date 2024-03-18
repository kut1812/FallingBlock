#ifndef __MOVEMENT_STATE__
#define __MOVEMENT_STATE__

#include "cocos2d.h"
#include "MovementState.h"

USING_NS_CC;
class MovementState {
public:
    virtual void enter() = 0;
    virtual void update(float dt) = 0;
    virtual void exit() = 0;
};


#endif // !__IDLE_STATE__
