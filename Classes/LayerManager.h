#ifndef __LAYER_MANAGER_H__
#define __LAYER_MANAGER_H__

#include "cocos2d.h"
#include "Character/Player.h"
USING_NS_CC;
class SQLiteManager;
class LayerManager
{
public:
	static LayerManager* getInstance();
	Node* settingLayer();
	Node* pauseLayer();
	void tutorialLayer1(Scene* scene);
	void tutorialLayer2(Scene* scene);
	Node* loseLayer(int score);
	Node* topListLayer();
	//Node* upgradeLayer();
	Node* storeLayer();
private:
	static LayerManager* _instance;
	SQLiteManager* dbManager;
	Player* _player;
};

#endif // !__LAYER_MANAGER_H__