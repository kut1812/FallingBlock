#ifndef __X_2_JUMP__
#define __X_2_JUMP__

#include "cocos2d.h"
#include "BaseSkill.h"

USING_NS_CC;
class Player;
class X2JumpSkill : BaseSkill, cocos2d::Node {
public:
    X2JumpSkill(Player* plr) : BaseSkill(plr) {}
    virtual bool init() override;
    virtual void use() override;
    virtual void setSkillCooldown(float newTime) override { skillCooldown = newTime; };
    virtual float getSkillCooldown() override { return this->skillCooldown; };
    virtual void setMaxSkillCooldown(float newTime) override { this->maxSkillCooldown = newTime; };
    virtual float getMaxSkillCooldown() override { return this->maxSkillCooldown; };
    ~X2JumpSkill();
};


#endif // !__X_2_JUMP__