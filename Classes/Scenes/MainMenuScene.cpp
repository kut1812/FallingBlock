#include "MainMenuScene.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LayerManager.h"
#include "UpgradeLayer.h"
#include "StoreLayer.h"
#include "WorkingWithData/SQLiteManager.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
	SQLiteManager* dbManager = SQLiteManager::getInstance();
	if (dbManager->init()) {
			dbManager->setPlayerInfo(1, 3, 300, 3, 2, 5, 0, 0, 0); // set or reset player 
			dbManager->addScore(1, 3222);
			dbManager->addScore(1, 2222);
			dbManager->addScore(1, 31222);
			dbManager->addScore(1, 53222);
			dbManager->addScore(1, 63222);
			dbManager->addScore(1, 73222);
			dbManager->addScore(1, 13222);
			dbManager->addScore(1, 23222);
			dbManager->addScore(1, 3322);
			dbManager->addScore(1, 342);
			dbManager->addScore(1, 122);

			/*SQLiteManager::PlayerInfo playerI4 = dbManager->getPlayerById(1);
			CCLOG("player id %d\nmoney %d\nmovement speed %f\nskill duration %f\nlife spawn %d", playerI4.id, playerI4.money, playerI4.movement_speed, playerI4.skill_duration, playerI4.life_spawn);*/


			/*for (auto i : dbManager->getTop10Highscore())
			{
				CCLOG("score %d: %d", i.playerId, i.score);
			}*/
	}
	else {
		CCLOG("false to loading db");
	}
	return MainMenuScene::create();
}

static void problemLoading(const char* filename) {
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainMenuScene::init() {
	if (!Scene::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	_player = Player::createPlayer();

	auto uiMenu = CSLoader::getInstance()->createNode("csb/MainMenu.csb");
	this->addChild(uiMenu);


	 auto buttonPlay = uiMenu->getChildByName<ui::Button*>("Button_2");
	 buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		 if (type == ui::Widget::TouchEventType::ENDED) {
			 //_player = Player::createPlayer(); // <-

			 auto newScene = GameScene::create(_player);
			 TransitionScene* transition = TransitionFade::create(0.5f, newScene, Color3B::WHITE);
			 Director::getInstance()->replaceScene(transition);
		 }
		 });

	 auto buttonSetting = uiMenu->getChildByName<ui::Button*>("Button_4");
	 buttonSetting->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		 if (type == ui::Widget::TouchEventType::ENDED) {
			 this->addChild(LayerManager::getInstance()->settingLayer());
		 }
		 });

	 auto buttonTutorial = uiMenu->getChildByName<ui::Button*>("Button_6");
	 buttonTutorial->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		 if (type == ui::Widget::TouchEventType::ENDED) {
			 LayerManager::getInstance()->tutorialLayer1(this);
		 }
		 });

	 auto buttonTopList = uiMenu->getChildByName<ui::Button*>("Button_7");
	 buttonTopList->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		 if (type == ui::Widget::TouchEventType::ENDED) {
			 this->addChild(LayerManager::getInstance()->topListLayer());
		 }
		 });

	 auto buttonUpgrade = uiMenu->getChildByName<ui::Button*>("Button_3");
	 buttonUpgrade->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		 if (type == ui::Widget::TouchEventType::ENDED) {
			 //this->addChild(LayerManager::getInstance()->upgradeLayer());
			 auto upgradeLayer = UpgradeLayer::create(_player);
			 this->addChild(upgradeLayer);
		 }
		 });

	 auto buttonStore = uiMenu->getChildByName<ui::Button*>("Button_5");
	 buttonStore->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		 if (type == ui::Widget::TouchEventType::ENDED) {
			 auto storeLayer = StoreLayer::create(_player);
			 this->addChild(storeLayer);
		 }
		 });

	return true;
}

