#ifndef __IDLE_STATE__
#define __IDLE_STATE__

#include "cocos2d.h"
#include "MovementState.h"

USING_NS_CC;
class Player;
class IdleState : public MovementState {
public:
    IdleState(Player* crt) : MovementState(crt) {}
    virtual void enter() override;
    virtual void update(float dt) override;
    virtual void exit() override;

};


#endif // !__IDLE_STATE__