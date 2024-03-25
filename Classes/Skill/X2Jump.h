#ifndef __X_2_JUMP__
#define __X_2_JUMP__

#include "cocos2d.h"
#include "BaseSkill.h"

USING_NS_CC;
class Player;
class X2JumpSkill : BaseSkill {
public:
    X2JumpSkill(Player* plr) : BaseSkill(plr) {}
    virtual bool init() override;
    virtual void use() override;
    ~X2JumpSkill();
};


#endif // !__X_2_JUMP__