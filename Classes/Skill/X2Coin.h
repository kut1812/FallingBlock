#ifndef __X_2_COIN__
#define __X_2_COIN__

#include "cocos2d.h"
#include "BaseSkill.h"

USING_NS_CC;
class Player;
class X2CoinSkill : BaseSkill {
public:
    X2CoinSkill(Player* plr) : BaseSkill(plr) {}
    virtual bool init() override;
    virtual void use() override;
    ~X2CoinSkill();
};


#endif // !__X_2_COIN__