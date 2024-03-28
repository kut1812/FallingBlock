#include "StoreLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Character/Player.h"
#include "Skill/X2Jump.h"
#include "Skill/Shield.h"
#include "Skill/X2Coin.h"
USING_NS_CC;
StoreLayer* StoreLayer::create(Player* _plr)
{
    StoreLayer* layer = new (std::nothrow) StoreLayer();
    if (layer && layer->init(_plr)) {
        layer->autorelease();
        return layer;
    }
    layer->_player = _plr;
    return nullptr;
}
bool StoreLayer::init(Player* _plr)
{
    if (!Layer::init()) {
        return false;
    }
    _player = _plr;
    dbManager = SQLiteManager::getInstance();


    Node* storeLayer = CSLoader::getInstance()->createNode("csb/Store.csb");
    Director::getInstance()->pause();

    auto cancel = storeLayer->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->resume();
            storeLayer->removeFromParentAndCleanup(true);
        }
        });

    auto watch = storeLayer->getChildByName<ui::Button*>("Button_2");
    watch->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //ads
        }
        });

    auto buyCoin = storeLayer->getChildByName<ui::Button*>("Button_4");
    buyCoin->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (unlockSkill("X2Coin")) {
                CCLOG("successfully!");
            }
            else {
                CCLOG("false!");
            }
        }
        });

    auto buyJump = storeLayer->getChildByName<ui::Button*>("Button_4_0");
    buyCoin->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (unlockSkill("X2Jump")) {
                CCLOG("successfully!");
            }
            else {
                CCLOG("false!");
            }
        }
        });

    auto buySheild = storeLayer->getChildByName<ui::Button*>("Button_4_1");
    buyCoin->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (unlockSkill("Shield")) {
                CCLOG("successfully!");
            }
            else {
                CCLOG("false!");
            }
        }
        });

    this->addChild(storeLayer);
    return true;
}

bool StoreLayer::unlockSkill(std::string skillName) {
    CCLOG("%d moneymoney", _player->getMoney());
    CCLOG("%s skillName", skillName.c_str());
    if (skillName == "X2Coin" && _player->getMoney() >= 10) {
        CCLOG("unlock x2 coin");
        if (!_player->getX2Coin()) {
            _player->decreaseMoney(10);
            _player->setSkillCoin(new X2CoinSkill(_player));
        }
    }
    else if (skillName == "X2Jump" && _player->getMoney() >= 15) {
        if (!_player->getX2Jump()) {
            _player->decreaseMoney(15); 
            _player->setSkillJump(new X2JumpSkill(_player));
        }
    }
    else if (skillName == "Shield" && _player->getMoney() >= 20) {
        if (!_player->getX2Jump()) {
            _player->decreaseMoney(20);
            _player->setSkillShield(new ShieldSkill(_player));
        }
    }
    else {
        return false;
    }
    dbManager->setPlayerInfo(1, _player->movementLevel, _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), _player->getX2Coin() ? 1 : 0, _player->getX2Jump() ? 1 : 0, _player->getShield() ? 1 : 0);
    return true;
}
