#ifndef __BASE_SKILL__
#define __BASE_SKILL__

#include "cocos2d.h"

USING_NS_CC;
class Player;
class BaseSkill {
public:
    //BaseSkill(Player* plr) : _player(plr) {}
    //virtual bool init();
    //CREATE_FUNC(BaseSkill);
protected:
    std::string skillName;
    float skillCooldown;
    float effectiveTime;
    Sprite* skillSprite;
    Player* _player;
};


#endif // !__BASE_SKILL__