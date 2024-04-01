#ifndef __X_2_COIN__
#define __X_2_COIN__

#include "cocos2d.h"
#include "BaseSkill.h"

USING_NS_CC;
class Player;
class X2CoinSkill : BaseSkill, cocos2d::Node {
public:
    X2CoinSkill(Player* plr, float maxDuration) : BaseSkill(plr, maxDuration) {}
    virtual bool init() override;
    virtual bool use() override;
    virtual void setSkillCooldown(float newTime) override { skillCooldown = newTime; };
    virtual float getSkillCooldown() override { return this->skillCooldown; }; // em get cái này ra nếu lớn hơn 0 thì hiển thị thôi (tương tự vs 2 skill kia)
    virtual void setMaxSkillCooldown(float newTime) override { this->maxSkillCooldown = newTime; };
    virtual float getMaxSkillCooldown() override { return this->maxSkillCooldown; };
   
    ~X2CoinSkill();
    Sprite* skillSprite;
private:

};


#endif // !__X_2_COIN__