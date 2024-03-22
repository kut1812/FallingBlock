#ifndef  __GAME_SCENE_H__
#define  __GAME_SCENE_H__

#include "cocos2d.h"
#include "../Character/Player.h"
#include "../Utilities/Joystick.h"
#include "../Utilities/JumpButton.h"
#include "../Actor/Block.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* create();
    virtual bool init();
    void updatePlayer(float dt);
    void setupPhysicBorder();
    void spawnBlocks(float dt);
private:
    bool OnContactBegan(cocos2d::PhysicsContact& contact);
private:
    Joystick* _joystick;
    JumpButton* _jumpButton;
    Player* _player;
    cocos2d::PhysicsWorld* world;
    void setPhysicsWorld(cocos2d::PhysicsWorld* m_world) {
        m_world = world;
    }
    float columnWidth;
    Size visibleSize;
    std::vector<std::vector<Block*>> listOfBlocks;

};

#endif // __GAME_SCENE_H__