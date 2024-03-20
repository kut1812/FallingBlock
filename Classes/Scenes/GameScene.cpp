#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "LayerManager.h"
#include "ui/CocosGUI.h"
USING_NS_CC;

Scene* GameScene::create()
{
    GameScene* scene = new GameScene();
    if (scene && scene->init())
    {
        scene->autorelease();
        return scene;
    }
    else
    {
        delete scene;
        return nullptr;
    }
}

bool GameScene::init()
{
    if (!Scene::init())
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto uiMenu = CSLoader::getInstance()->createNode("csb/Layer.csb");
    this->addChild(uiMenu);

    auto pause = uiMenu->getChildByName<ui::Button*>("Button_3");
    pause->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            this->addChild(LayerManager::getInstance()->pauseLayer(),100);
        }
        });
   
    _player = Player::createPlayer();
    _player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(_player,3);
    

    return true;
}

