#include "LayerManager.h"
#include "AudioEngine.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "Scenes/GameScene.h"
#include "Scenes/MainMenuScene.h"

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
