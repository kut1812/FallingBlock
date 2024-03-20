#ifndef  __MAIN_MENU_SCENE_H__
#define  __MAIN_MENU_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;

class MainMenuScene :public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
private:
	CREATE_FUNC(MainMenuScene);
};
#endif // __MAIN_MENU_SCENE_H__

