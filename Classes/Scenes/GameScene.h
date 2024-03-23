#ifndef  __GAME_SCENE_H__
#define  __GAME_SCENE_H__

#include "cocos2d.h"
#include "../Character/Player.h"
#include "../Utilities/Joystick.h"
#include "../Utilities/JumpButton.h"
#include "../Actor/Block.h"
#include "../Utilities/MileageCounter.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* create();
    virtual bool init();
    void updatePlayer(float dt);
    void updateMeter(float dt);
    void setupPhysicBorder();
    void spawnBlocks(float dt);

private:
    float currentMeter = 0;
    float limitMeter = 20;
    float savedMeterBe4Reset = 0;
    MileageCounter* mileageCounter;
    Joystick* _joystick;
    JumpButton* _jumpButton;
    Player* _player;
    cocos2d::PhysicsWorld* world;
    float columnWidth;
    Size visibleSize;
    bool flag = false;
    std::vector<Block*> listOfBlocks;
    float listPositionYBlock[14];
    
    bool OnContactBegan(cocos2d::PhysicsContact& contact);
    void setPhysicsWorld(cocos2d::PhysicsWorld* m_world) {
        m_world = world;
    }
    float findMin(float arr[], int size) {
        float minValue = arr[0];
        for (int i = 1; i < size; ++i) {
            if (arr[i] < minValue) {
                minValue = arr[i];
            }
        }
        return minValue;
    }
};

#endif // __GAME_SCENE_H__