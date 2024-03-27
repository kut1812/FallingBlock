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
            auto newScene = GameScene::create();
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

Node* LayerManager::loseLayer()
{
    Node* loseLayer = CSLoader::getInstance()->createNode("csb/Lose.csb");
    Director::getInstance()->pause();
    auto home = loseLayer->getChildByName<ui::Button*>("Button_6");
    home->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto newScene = MainMenuScene::createScene();
            TransitionScene* transition = TransitionFade::create(0.5f, newScene, Color3B::WHITE);
            Director::getInstance()->resume();
            Director::getInstance()->replaceScene(transition);
        }
        });

    auto topList = loseLayer->getChildByName<ui::Button*>("Button_7");
    topList->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            loseLayer->addChild(LayerManager::getInstance()->topListLayer());
        }
        });

    auto restart = loseLayer->getChildByName<ui::Button*>("Button_6_0");
    restart->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            auto newScene = GameScene::create();
            TransitionScene* transition = TransitionFade::create(0.5f, newScene, Color3B::WHITE);
            Director::getInstance()->resume();
            Director::getInstance()->replaceScene(transition);
        }
        });
    
    return loseLayer;
}

Node* LayerManager::topListLayer()
{
    Node* topListLayer = CSLoader::getInstance()->createNode("csb/LeaderBoard.csb");
    Director::getInstance()->pause();

    auto cancel = topListLayer->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->resume();
            topListLayer->removeFromParentAndCleanup(true);
        }
        });
    return topListLayer;
}

Node* LayerManager::upgradeLayer()
{
    SQLiteManager* dbManager = SQLiteManager::getInstance();

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Node* upgradeLayer = CSLoader::getInstance()->createNode("csb/Upgrade.csb");
    Director::getInstance()->pause();

    auto cancel = upgradeLayer->getChildByName<ui::Button*>("Button_3");
    cancel->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            Director::getInstance()->resume();
            upgradeLayer->removeFromParentAndCleanup(true);
        }
        });

    auto textLevelSkullSpeed = Label::createWithTTF("  0/300","font/Baloo2/Baloo2-Bold.ttf",20);
    textLevelSkullSpeed->setPosition(Vec2(visibleSize.width * 0.31, visibleSize.height * 0.56));
    textLevelSkullSpeed->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(textLevelSkullSpeed);
    auto textLifeSpawn = Label::createWithTTF("  0/300","font/Baloo2/Baloo2-Bold.ttf",20);
    textLifeSpawn->setPosition(Vec2(visibleSize.width * 0.53, visibleSize.height * 0.56));
    textLifeSpawn->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(textLifeSpawn);
    auto textBlockSpeed = Label::createWithTTF("  0/300", "font/Baloo2/Baloo2-Bold.ttf", 20);
    textBlockSpeed->setPosition(Vec2(visibleSize.width * 0.31, visibleSize.height * 0.35));
    textBlockSpeed->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(textBlockSpeed);
    auto textSkillDuration = Label::createWithTTF("  0/300", "font/Baloo2/Baloo2-Bold.ttf", 20);
    textSkillDuration->setPosition(Vec2(visibleSize.width * 0.53, visibleSize.height * 0.35));
    textSkillDuration->setAnchorPoint(Vec2(0, 0.5));
    upgradeLayer->addChild(textSkillDuration);
    
    auto textCoin = Label::createWithTTF("0", "font/Baloo2/Baloo2-Bold.ttf", 20);
    textCoin->setPosition(Vec2(visibleSize.width * 0.51, visibleSize.height * 0.20));
    upgradeLayer->addChild(textCoin);


    //SkullSpeed
    int levelSkullSpeed = dbManager->getPlayerById(1).movement_speed;

    Vector<Sprite*> loadingSkullSpeed;
    for (int i = 0; i < 10; ++i) {
        auto section = Sprite::create("popup/fb_popup_upgrade_cell_b.png"); // Hình ảnh mặc định là màu đen
        section->setPosition(Vec2(visibleSize.width * 0.33 + (i*visibleSize.width*0.013), visibleSize.height * 0.62)); // Đặt vị trí cho từng khúc
        section->setScale(0.5);
        upgradeLayer->addChild(section);
        loadingSkullSpeed.pushBack(section);
    }
    for (int i = 0; i < levelSkullSpeed%10; ++i) {
        loadingSkullSpeed.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
    }
    
    auto buttonAddSS= upgradeLayer->getChildByName<ui::Button*>("fb_popup_upgrade_plus_a_10");
    buttonAddSS->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            //levelSkullSpeed += 1;
            //loadingSkullSpeed.at(levelSkullSpeed % 10 + 1);
        }
        });
    
        //LifeSpawn
    int levelLifeSpawn = dbManager->getPlayerById(1).life_spawn;

    Vector<Sprite*> loadingLifeSpawn;
    for (int i = 0; i < 10; ++i) {
        auto section = Sprite::create("popup/fb_popup_upgrade_cell_b.png"); // Hình ảnh mặc định là màu đen
        section->setPosition(Vec2(visibleSize.width * 0.55 + (i*visibleSize.width*0.013), visibleSize.height * 0.62)); // Đặt vị trí cho từng khúc
        section->setScale(0.5);
        upgradeLayer->addChild(section);
        loadingLifeSpawn.pushBack(section);
    }
    for (int i = 0; i < levelLifeSpawn % 10; ++i) {
        loadingLifeSpawn.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
    }
    

    //BlockSpeed
    int levelBlockSpeed = dbManager->getPlayerById(1).block_speed;

    Vector<Sprite*> loadingBlockSpeed;
    for (int i = 0; i < 10; ++i) {
        auto section = Sprite::create("popup/fb_popup_upgrade_cell_b.png"); // Hình ảnh mặc định là màu đen
        section->setPosition(Vec2(visibleSize.width * 0.33 + (i*visibleSize.width*0.013), visibleSize.height * 0.40)); // Đặt vị trí cho từng khúc
        section->setScale(0.5);
        upgradeLayer->addChild(section);
        loadingBlockSpeed.pushBack(section);
    }
    for (int i = 0; i < levelBlockSpeed % 10; ++i) {
        loadingBlockSpeed.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
    }
    
    
    //SkillDuration
    int levelSkillDuration = dbManager->getPlayerById(1).skill_duration;

    Vector<Sprite*> loadingSkillDuration;
    for (int i = 0; i < 10; ++i) {
        auto section = Sprite::create("popup/fb_popup_upgrade_cell_b.png"); // Hình ảnh mặc định là màu đen
        section->setPosition(Vec2(visibleSize.width * 0.55 + (i*visibleSize.width*0.013), visibleSize.height * 0.40)); // Đặt vị trí cho từng khúc
        section->setScale(0.5);
        upgradeLayer->addChild(section);
        loadingSkillDuration.pushBack(section);
    }
    for (int i = 0; i < levelSkillDuration % 10; ++i) {
        loadingSkillDuration.at(i)->setTexture("popup/fb_popup_upgrade_cell_a.png");
    }

    return upgradeLayer;
}

Node* LayerManager::storeLayer()
{
    Node* storeLayer = CSLoader::getInstance()->createNode("csb/LeaderBoard.csb");
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
        }
        });

    auto buyJump = storeLayer->getChildByName<ui::Button*>("Button_4");
    buyCoin->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
           //
        }
        });

    auto buySheild = storeLayer->getChildByName<ui::Button*>("Button_4");
    buyCoin->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
           //
        }
        });
    return storeLayer;
}
