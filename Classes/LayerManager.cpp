#include "LayerManager.h"
#include "AudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Scenes/GameScene.h"
#include "Scenes/MainMenuScene.h"
#include "StatsManager/StatsManager.h"
#include "WorkingWithData/SQLiteManager.h"

LayerManager* LayerManager::_instance;

LayerManager* LayerManager::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new LayerManager();
    }
    _instance->dbManager = SQLiteManager::getInstance();
    return _instance;
}

Node* LayerManager::settingLayer()
{
    Node* settingLayer = CSLoader::getInstance()->createNode("csb/Setting.csb");
    
    auto cancel = settingLayer->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            settingLayer->removeFromParentAndCleanup(true);
        }
        });

    auto checkboxSFX = settingLayer->getChildByName<ui::CheckBox*>("Button_4");
    checkboxSFX->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (checkboxSFX->isSelected() == true)
            {
            checkboxSFX->setSelected(false);
            }
            else
            {
            checkboxSFX->setSelected(true);
            }
        }
        });

    auto checkboxMusic = settingLayer->getChildByName<ui::CheckBox*>("Button_5");
    checkboxMusic->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (checkboxMusic->isSelected() == true)
            {
                checkboxMusic->setSelected(false);
            }
            else
            {
                checkboxMusic->setSelected(true);
            }
        }
        });

    return settingLayer;
}

Node* LayerManager::pauseLayer()
{
    Node* pauseLayer = CSLoader::getInstance()->createNode("csb/Pause.csb");
    Director::getInstance()->pause();

    auto cancel = pauseLayer->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->resume();
            pauseLayer->removeFromParentAndCleanup(true);
        }
        });

    auto checkboxSFX = pauseLayer->getChildByName<ui::CheckBox*>("Button_4");
    checkboxSFX->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (checkboxSFX->isSelected() == true)
            {
                checkboxSFX->setSelected(false);
            }
            else
            {
                checkboxSFX->setSelected(true);
            }
        }
        });

    auto checkboxMusic = pauseLayer->getChildByName<ui::CheckBox*>("Button_5");
    checkboxMusic->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            if (checkboxMusic->isSelected() == true)
            {
                checkboxMusic->setSelected(false);
            }
            else
            {
                checkboxMusic->setSelected(true);
            }
        }
        });

    auto home = pauseLayer->getChildByName<ui::Button*>("Button_6");
    home->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto newScene = MainMenuScene::createScene();
            TransitionScene* transition = TransitionFade::create(0.5f, newScene, Color3B::WHITE);
            Director::getInstance()->resume();
            Director::getInstance()->replaceScene(transition);
        }
        });

    auto toplist = pauseLayer->getChildByName<ui::Button*>("Button_7");
    toplist->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->resume();
            pauseLayer->removeFromParentAndCleanup(true);
        }
        });

    auto restart = pauseLayer->getChildByName<ui::Button*>("Button_6_0");
    restart->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            _player = Player::createPlayer();
            auto newScene = GameScene::create(_player);
            TransitionScene* transition = TransitionFade::create(0.5f, newScene, Color3B::WHITE);
            Director::getInstance()->resume();
            Director::getInstance()->replaceScene(transition);
        }
        });

    return pauseLayer;
}

void LayerManager::tutorialLayer1(Scene* scene)
{
    Node* tutorialLayer = CSLoader::getInstance()->createNode("csb/Tutorial1.csb");
    
    auto cancel = tutorialLayer->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            tutorialLayer->removeFromParentAndCleanup(true);
        }
        });

    auto next = tutorialLayer->getChildByName<ui::Button*>("Button_3_0");
    next->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            tutorialLayer->removeFromParentAndCleanup(true);
            tutorialLayer2(scene);
        }
        });
    scene->addChild(tutorialLayer);
    
}

void LayerManager::tutorialLayer2(Scene* scene)
{
    Node* tutorialLayer2 = CSLoader::getInstance()->createNode("csb/Tutorial2.csb");

    auto cancel = tutorialLayer2->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            tutorialLayer2->removeFromParentAndCleanup(true);
        }
        });

    auto back = tutorialLayer2->getChildByName<ui::Button*>("Button_3_0_0");
    back->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            tutorialLayer2->removeFromParentAndCleanup(true);
            tutorialLayer1(scene);
        }
        });
    scene->addChild(tutorialLayer2);
}

Node* LayerManager::loseLayer(int score, Player* player)
{
    Node* loseLayer = CSLoader::getInstance()->createNode("csb/Lose.csb");
    Director::getInstance()->pause();
    auto home = loseLayer->getChildByName<ui::Button*>("Button_6");
    home->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto dbManager = SQLiteManager::getInstance();
            dbManager->addScore(1, score);
            dbManager->setPlayerInfo(1, player->getMovementLevel(), player->getMoney() + CoinManager::getInstance()->getCoin(), player->getLifeSpawnLevel(), player->getBlockSpeedLevel(), player->getSkillDurationLevel(), player->getCoinAmount(), player->getJumpAmount(), player->getShieldAmount());
            auto newScene = MainMenuScene::createScene();
            TransitionScene* transition = TransitionFade::create(0.5f, newScene, Color3B::WHITE);
            Director::getInstance()->resume();
            Director::getInstance()->replaceScene(transition);
        }
        });

    auto topList = loseLayer->getChildByName<ui::Button*>("Button_7");
    topList->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto dbManager = SQLiteManager::getInstance();
            dbManager->addScore(1, score);
            dbManager->setPlayerInfo(1, player->getMovementLevel(), player->getMoney() + CoinManager::getInstance()->getCoin(), player->getLifeSpawnLevel(), player->getBlockSpeedLevel(), player->getSkillDurationLevel(), player->getCoinAmount(), player->getJumpAmount(), player->getShieldAmount());
            loseLayer->addChild(LayerManager::getInstance()->topListLayer());
        }
        });

    auto restart = loseLayer->getChildByName<ui::Button*>("Button_6_0");
    restart->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto dbManager = SQLiteManager::getInstance();
            dbManager->addScore(1, score);
            dbManager->setPlayerInfo(1, player->getMovementLevel(), player->getMoney() + CoinManager::getInstance()->getCoin(), player->getLifeSpawnLevel(), player->getBlockSpeedLevel(), player->getSkillDurationLevel(), player->getCoinAmount(), player->getJumpAmount(), player->getShieldAmount());
            _player = Player::createPlayer();
            auto newScene = GameScene::create(_player);
            TransitionScene* transition = TransitionFade::create(0.5f, newScene, Color3B::WHITE);
            Director::getInstance()->resume();
            Director::getInstance()->replaceScene(transition);
        }
        });
    
    return loseLayer;
}

Node* LayerManager::topListLayer()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Node* topListLayer = CSLoader::getInstance()->createNode("csb/LeaderBoard.csb");
    Director::getInstance()->pause();

    auto cancel = topListLayer->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->resume();
            topListLayer->removeFromParentAndCleanup(true);
        }
        });

    std::vector<SQLiteManager::ScoreInfo> top10 = dbManager->getTop10Highscore();
    
    float offsetX = 0.49;
    float offsetY = 0.62;
    for (int i = 0; i < 10; i++) {
        if (i < top10.size()) {
            auto textp1 = Label::createWithTTF(std::to_string(top10[i].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
            textp1->setPosition(Vec2(visibleSize.width * offsetX, visibleSize.height * offsetY));
            textp1->setAnchorPoint(Vec2(1, 0.5));
            topListLayer->addChild(textp1);
            if (i == 4) {
                offsetY = 0.69;
                offsetX = 0.71;
            }
            offsetY -= 0.07;
        }
        else {
            auto textp1 = Label::createWithTTF(std::to_string(0), "font/Baloo2/Baloo2-Bold.ttf", 20);
            textp1->setPosition(Vec2(visibleSize.width * offsetX, visibleSize.height * offsetY));
            textp1->setAnchorPoint(Vec2(1, 0.5));
            topListLayer->addChild(textp1);
            if (i == 4) {
                offsetY = 0.69;
                offsetX = 0.71;
            }
            offsetY -= 0.07;
        }
    }

    //auto textp1 = Label::createWithTTF(std::to_string(top10[0].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp1->setPosition(Vec2(visibleSize.width * 0.49, visibleSize.height * 0.62));
    //textp1->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp1);
    // auto textp2 = Label::createWithTTF(std::to_string(top10[1].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp2->setPosition(Vec2(visibleSize.width * 0.49, visibleSize.height * 0.55));
    //textp2->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp2);
    // auto textp3 = Label::createWithTTF(std::to_string(top10[2].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp3->setPosition(Vec2(visibleSize.width * 0.49, visibleSize.height * 0.48));
    //textp3->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp3);
    // auto textp4 = Label::createWithTTF(std::to_string(top10[3].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp4->setPosition(Vec2(visibleSize.width * 0.49, visibleSize.height * 0.41));
    //textp4->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp4);
    // auto textp5 = Label::createWithTTF(std::to_string(top10[4].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp5->setPosition(Vec2(visibleSize.width * 0.49, visibleSize.height * 0.34));
    //textp5->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp5);
    // auto textp6 = Label::createWithTTF(std::to_string(top10[5].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp6->setPosition(Vec2(visibleSize.width * 0.71, visibleSize.height * 0.62));
    //textp6->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp6);
    // auto textp7 = Label::createWithTTF(std::to_string(top10[6].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp7->setPosition(Vec2(visibleSize.width * 0.71, visibleSize.height * 0.55));
    //textp7->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp7);
    // auto textp8 = Label::createWithTTF(std::to_string(top10[7].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp8->setPosition(Vec2(visibleSize.width * 0.71, visibleSize.height * 0.48));
    //textp8->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp8);
    // auto textp9 = Label::createWithTTF(std::to_string(top10[8].score), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp9->setPosition(Vec2(visibleSize.width * 0.71, visibleSize.height * 0.41));
    //textp9->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp9);
    //auto textp10 = Label::createWithTTF(std::to_string((top10[9].id != -1 ? top10[89].score : 0)), "font/Baloo2/Baloo2-Bold.ttf", 20);
    //textp10->setPosition(Vec2(visibleSize.width * 0.71, visibleSize.height * 0.34));
    //textp10->setAnchorPoint(Vec2(1, 0.5));
    //topListLayer->addChild(textp10);

    return topListLayer;
}

Node* LayerManager::storeLayer()
{
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
           //
           // StoreLayer* strLayer
        }
        });

    auto buyJump = storeLayer->getChildByName<ui::Button*>("Button_4_0");
    buyCoin->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
           //
        }
        });

    auto buySheild = storeLayer->getChildByName<ui::Button*>("Button_4_1");
    buyCoin->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
           //
        }
        });
    return storeLayer;
}