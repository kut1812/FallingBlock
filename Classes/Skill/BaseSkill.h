#ifndef __BASE_SKILL__
#define __BASE_SKILL__

#include "cocos2d.h"

USING_NS_CC;
class Player;
class BaseSkill {
public:
    BaseSkill(Player* plr) : _player(plr) {}
    virtual bool init() = 0;
    virtual void use() = 0;
protected:
    std::string skillName;
    float skillCooldown;
    float effectiveTime;
    Sprite* skillSprite;
    Player* _player;
};


#endif // !__BASE_SKILL__