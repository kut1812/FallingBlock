#ifndef __PLAYER__
#define __PLAYER__

#include "cocos2d.h"
#include "../State/IdleState.h"
#include "../State/MoveLeftState.h"
#include "../State/MoveRightState.h"
#include "../State/JumpingState.h"

USING_NS_CC;
class Player : public cocos2d::Node
{
public:
	static Player* createPlayer();
	virtual bool init();
	enum class PlayerState {
		IDLE,
		MOVE_LEFT,
		MOVE_RIGHT,
		JUMPING
	};
	void update(float dt);
	void changeState(PlayerState newState);
	Sprite* getSprite() const { return characterSprite; };
private:
	MovementState* currentState = nullptr;
	IdleState* idleState;
	MoveLeftState* moveLeftState;
	MoveRightState* moveRightState;
	//JumpingState *jumpingState;
	Sprite* characterSprite;
};

#endif // !__PLAYER__