#include "MainMenuScene.h"
#include "GameScene.h"
#include "ui/CocosGUI.h"
#include "AudioEngine.h"
#include "Utilities/AnimationUtils.h"
#include "SettingsScene.h"
#include "Audio/AudioManager.h"
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

	/*int id = AudioEngine::play2d("Audio/ALoi-Double2TMasew-10119691.mp3", true, 1.0f);*/
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("background.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	float scaleX = visibleSize.width / background->getContentSize().width;
	float scaleY = visibleSize.height / background->getContentSize().height;
	background->setScaleX(scaleX);
	background->setScaleY(scaleY);
	this->addChild(background,0);

	auto background1 = Sprite::create("title_flappybird.png");
	background1->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.7));
	background1->setScale(2.f);
	this->addChild(background1, 0);

	auto bird1 = Sprite::create("bird.png");
	bird1->setPosition(visibleSize *0.535);
	addChild(bird1, 5);
	AnimationUtils::loadSpriteFrameCache("birdAnimation/", "bird");
	auto ani = AnimationUtils::createAnimation("bird", 0.5f);
	Animate* animate = Animate::create(ani.first);
	bird1->runAction(RepeatForever::create(animate));
	bird1->setScale(5.0f);

	//button2->setTitleText("");
	//button2->setTitleColor(Color3B::BLACK); 
	auto buttonStartGame = ui::Button::create("StartGameGreen.png", "StartGameRed.png");
	buttonStartGame->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(GameScene::createScene());
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonStartGame->setPosition(Vec2(visibleSize.width / 2, visibleSize.height *0.4));
	this->addChild(buttonStartGame);


	auto buttonSettings = ui::Button::create("SettingsGreen.png", "SettingsRed.png");
	buttonSettings->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->replaceScene(TransitionFade::create(2, SettingsScene::createScene()));
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonSettings->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3));
	this->addChild(buttonSettings);

	auto buttonExit = ui::Button::create("ExitGreen.png", "ExitRed.png");
	buttonExit->addTouchEventListener(
		[&](Ref* sender, ui::Widget::TouchEventType type) {
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				break;
			case ui::Widget::TouchEventType::ENDED:
				Director::getInstance()->end();
				break;
			case ui::Widget::TouchEventType::CANCELED:
				break;
			default:
				break;
			}});
	buttonExit->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.2));
	this->addChild(buttonExit);
	return true;
}