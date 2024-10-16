﻿#include "StoreLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Character/Player.h"
#include "Skill/X2Jump.h"
#include "Skill/Shield.h"
#include "Skill/X2Coin.h"
#include "CoinManager/CoinManager.h"
#include "Scenes/GameScene.h"
USING_NS_CC;
StoreLayer* StoreLayer::create(Player* _plr)
{
    StoreLayer* layer = new (std::nothrow) StoreLayer();
    if (layer && layer->init(_plr)) {
        layer->autorelease();
        return layer;
    }
    layer->_player = _plr;
    layer->dbManager = SQLiteManager::getInstance();

    return nullptr;
}
bool StoreLayer::init(Player* _plr)
{
    if (!Layer::init()) {
        return false;
    }
    _player = _plr;
    dbManager = SQLiteManager::getInstance();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->scheduleUpdate();
    Node* storeLayer = CSLoader::getInstance()->createNode("csb/Store.csb");
    Director::getInstance()->pause();

    auto cancel = storeLayer->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->resume();
            auto sceneGame1 = dynamic_cast<GameScene*>(Director::getInstance()->getRunningScene());
            if (sceneGame1 != nullptr) {
                sceneGame1->setDynamicAllBlock(true);
            }
            storeLayer->removeFromParentAndCleanup(true);
            coin = nullptr;
        }
        });

    auto watch = storeLayer->getChildByName<ui::Button*>("Button_1");
    watch->setEnabled(false);
    watch->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            CCLOG("1");
        }
        });

    auto buyCoin = storeLayer->getChildByName<ui::Button*>("Button_1_0");
    
    if(_player->getMoney() < 20)
        buyCoin->setEnabled(false);
    buyCoin->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Button::TouchEventType::BEGAN:
            // Khi nút được nhấn, phóng to nút lên
            //buyCoin->setScale(0.55f);
            break;
        case ui::Button::TouchEventType::ENDED:
            if (unlockSkill("X2Coin")) {
                x2coin->setString(std::to_string(_player->getCoinAmount()));
                coin->setString(std::to_string(_player->getMoney()));
                if (_player->getMoney() < 20) {
                    buyCoin->setEnabled(false);
                }
            }
            else {
                CCLOG("false!");
            }
            //buyCoin->setScale(0.5);
            break;
        default:
            break;
        }
        });

    auto buyJump = storeLayer->getChildByName<ui::Button*>("Button_1_0_0");

    if (_player->getMoney() < 30)
        buyJump->setEnabled(false);
    buyJump->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Button::TouchEventType::BEGAN:
            // Khi nút được nhấn, phóng to nút lên
            //buyJump->setScale(0.55);
            break;
        case ui::Button::TouchEventType::ENDED:
            if (unlockSkill("X2Jump")) {
                x2jump->setString(std::to_string(_player->getJumpAmount()));
                coin->setString(std::to_string(_player->getMoney()));
                if (_player->getMoney() < 30) {
                    buyJump->setEnabled(false);
                }
            }
            else {
                CCLOG("false!");
            }
            //buyJump->setScale(0.5);
            break;
        default:
            break;
        }
        });

    auto buySheild = storeLayer->getChildByName<ui::Button*>("Button_1_0_0_0");

    if (_player->getMoney() < 40)
        buySheild->setEnabled(false);
    buySheild->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        switch (type)
        {
        case ui::Button::TouchEventType::BEGAN:
            // Khi nút được nhấn, phóng to nút lên
            //buySheild->setScale(0.55);
            break;
        case ui::Button::TouchEventType::ENDED:
            if (type == ui::Widget::TouchEventType::ENDED) {
                if (unlockSkill("Shield")) {
                    textShield->setString(std::to_string(_player->getShieldAmount()));
                    coin->setString(std::to_string(_player->getMoney()));
                    if (_player->getMoney() < 40) {
                        buySheild->setEnabled(false);
                    }
                }
                else {
                    CCLOG("false!");
                }
            }
            //buySheild->setScale(0.5);
            break;
        default:
            break;
        }
        });
    //label coin
    coin = Label::createWithTTF(std::to_string(_player->getMoney()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    coin->setPosition(Vec2(visibleSize.width * 0.62, visibleSize.height * 0.31));
    storeLayer->addChild(coin, 1);
    //label x2jump
    x2jump = Label::createWithTTF(std::to_string(_player->getJumpAmount()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    x2jump->setPosition(Vec2(visibleSize.width * 0.38, visibleSize.height * 0.31));
    storeLayer->addChild(x2jump, 1);
    //label shield
    textShield = Label::createWithTTF(std::to_string(_player->getShieldAmount()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    textShield->setPosition(Vec2(visibleSize.width * 0.45, visibleSize.height * 0.31));
    storeLayer->addChild(textShield, 1);
    //label x2coin
    x2coin = Label::createWithTTF(std::to_string(_player->getCoinAmount()), "font/Baloo2/Baloo2-Bold.ttf", 20);
    x2coin->setPosition(Vec2(visibleSize.width * 0.52, visibleSize.height * 0.31));
    storeLayer->addChild(x2coin, 1);
    this->addChild(storeLayer);
    /*dbManager->addScore(1, score);*/
    return true;
}

bool StoreLayer::unlockSkill(std::string skillName) {
    if (skillName == "X2Coin" && _player->getMoney() >= 10) {
        _player->decreaseMoney(10);
        _player->increaseCoinAmount(1);
    }
    else if (skillName == "X2Jump" && _player->getMoney() >= 20) {
        _player->decreaseMoney(20);
        _player->increaseJumpAmount(1);
    }
    else if (skillName == "Shield" && _player->getMoney() >= 30) {
        _player->decreaseMoney(30);
        _player->increaseShieldAmount(1);
    }
    else {
        return false;
    }
    dbManager->setPlayerInfo(1, _player->movementLevel, _player->getMoney(), _player->getLifeSpawnLevel(), _player->getBlockSpeedLevel(), _player->getSkillDurationLevel(), _player->getCoinAmount(), _player->getJumpAmount(), _player->getShieldAmount());
    return true;
}