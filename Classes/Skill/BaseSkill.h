#ifndef __BASE_SKILL__
#define __BASE_SKILL__

#include "cocos2d.h"

USING_NS_CC;
class Player;
class BaseSkill  {
public:
    BaseSkill(Player* plr, float maxDuration) : _player(plr), maxSkillCooldown(maxDuration) {}
    virtual bool init() = 0;
    virtual bool use() = 0;
    virtual void setSkillCooldown(float newTime) = 0;
    virtual float getSkillCooldown() = 0;
    virtual void setMaxSkillCooldown(float newTime) = 0;
    virtual float getMaxSkillCooldown() = 0;
protected:
    std::string skillName;
    float skillCooldown;
    float maxSkillCooldown;
    float effectiveTime;
    Player* _player;
};


#endif // !__BASE_SKILL__