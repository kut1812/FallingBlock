#ifndef __MOVE_LEFT_STATE__
#define __MOVE_LEFT_STATE__

#include "cocos2d.h"
#include "MovementState.h"

USING_NS_CC;
class Player;
class MoveLeftState : public MovementState {
public:
    MoveLeftState(Player* crt) : MovementState(crt) {}
    virtual void enter() override;
    virtual void update(float dt) override;
    virtual void exit() override;
};


#endif // !__IDLE_STATE__