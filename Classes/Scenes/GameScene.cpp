#include "GameScene.h"
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

    auto background = Sprite::create("background_home.png");
    background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.5));
    background->setScale(visibleSize.height / background->getContentSize().height);
    this->addChild(background);

    auto backgroundplay = Sprite::create("background_play.png");
    backgroundplay->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.5));
    backgroundplay->setScale(visibleSize.height / backgroundplay->getContentSize().height);
    this->addChild(backgroundplay,1);

    _player = Player::createPlayer();
    _player->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    this->addChild(_player,5);
    

    return true;
}

