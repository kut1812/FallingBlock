#ifndef __SHIELD_SKILL__
#define __SHIELD_SKILL__

#include "cocos2d.h"
#include "BaseSkill.h"

USING_NS_CC;
class Player;
class ShieldSkill : BaseSkill {
public:
    //ShieldSkill(Player* plr) : BaseSkill(plr) {}
    virtual bool init();
    //CREATE_FUNC(ShieldSkill);
};


#endif // !__SHIELD_SKILL__