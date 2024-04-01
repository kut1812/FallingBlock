#ifndef __UPGRADE_LAYER_H__
#define __UPGRADE_LAYER_H__

#include "cocos2d.h"
#include "Character/Player.h"
#include"Scenes/GameScene.h"
#include <iomanip> 
#include <sstream>
class UpgradeLayer : public cocos2d::Layer {
public:
    static UpgradeLayer* create(Player* _plr);
    virtual bool init(Player* _plr) ;
private:
    Player* _player;
};

#endif // __UPGRADE_LAYER_H__
