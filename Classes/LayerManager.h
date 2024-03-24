#ifndef __LAYER_MANAGER_H__
#define __LAYER_MANAGER_H__

#include "cocos2d.h"
#include"Scenes/GameScene.h"
USING_NS_CC;
class LayerManager
{
public:
	static LayerManager* getInstance();
	Node* settingLayer();
	Node* pauseLayer();
	void tutorialLayer1(Scene* scene);
	void tutorialLayer2(Scene* scene);
	Node* loseLayer();
private:
	static LayerManager* _instance;

	int _amount;
};

#endif // !__LAYER_MANAGER_H__