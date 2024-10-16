#ifndef __SHIELD_SKILL__
#define __SHIELD_SKILL__

#include "cocos2d.h"
#include "BaseSkill.h"

USING_NS_CC;
class Player;
class ShieldSkill : BaseSkill {
public:
    ShieldSkill(Player* plr, float maxDuration) : BaseSkill(plr, maxDuration) {}
    virtual bool init() override;
    virtual bool use() override;
    virtual void setSkillCooldown(float newTime) override { skillCooldown = newTime; };
    virtual float getSkillCooldown() override { return this->skillCooldown; } ;
    virtual void setMaxSkillCooldown(float newTime) override { this->maxSkillCooldown = newTime; };
    virtual float getMaxSkillCooldown() override { return this->maxSkillCooldown; };
  
    ~ShieldSkill();
    Sprite* skillSprite;
private:

};


#endif // !__SHIELD_SKILL__