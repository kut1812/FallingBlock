#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
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
    //uiMenu->setAnchorPoint(Vec2(0.5, 0.5));
    //uiMenu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(uiMenu);
    /*
    auto block = Sprite::create("block.png");
    block->setPosition(Vec2(0, visibleSize.height * 0.5));
    block->setScale(visibleSize.height / block->getContentSize().height);
    block->setAnchorPoint(Vec2(0, 0.5));
    this->addChild(block,3);

    auto block2 = Sprite::create("block.png");
    block2->setPosition(Vec2(visibleSize.width, visibleSize.height * 0.5));
    block2->setScale(visibleSize.height / block2->getContentSize().height);
    block2->setAnchorPoint(Vec2(1, 0.5));
    this->addChild(block2,3);

    auto backgroundplay = Sprite::create("background_play.png");
    backgroundplay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.5));
    backgroundplay->setScale(visibleSize.height / backgroundplay->getContentSize().height);
    this->addChild(backgroundplay,2);*/

    _player = Player::createPlayer();
    _player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(_player,3);
    

    return true;
}

