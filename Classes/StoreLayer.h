#ifndef __STORE_LAYER_H__
#define __STORE_LAYER_H__

#include "cocos2d.h"
#include "Skill/BaseSkill.h"
#include "Skill/Shield.h"
#include "Skill/X2Coin.h"
#include "Skill/X2Jump.h"
#include "WorkingWithData/SQLiteManager.h"

USING_NS_CC;

class StoreLayer :public cocos2d::Layer{
public:
    static StoreLayer* create(Player* _plr);
    virtual bool init(Player* _plr);
    bool unlockSkill(std::string skillName);
private:
    Player* _player;
    SQLiteManager* dbManager;
};

#endif // !__STORE_LAYER_H__
