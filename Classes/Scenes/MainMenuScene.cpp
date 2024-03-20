#include "MainMenuScene.h"
#include "GameScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LayerManager.h"
USING_NS_CC;

Scene* MainMenuScene::createScene()
{
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

	auto uiMenu = CSLoader::getInstance()->createNode("csb/MainMenu.csb");
	this->addChild(uiMenu);


	 auto buttonPlay = uiMenu->getChildByName<ui::Button*>("Button_2");
	 buttonPlay->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		 if (type == ui::Widget::TouchEventType::ENDED) {
			 auto newScene = GameScene::create(); 
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

	return true;
}

