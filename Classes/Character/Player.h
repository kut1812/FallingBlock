#ifndef __PLAYER__
#define __PLAYER__

#include "cocos2d.h"
#include "../State/IdleState.h"
#include "../State/IdleLeftState.h"
#include "../State/MoveLeftState.h"
#include "../State/MoveRightState.h"
#include "../State/JumpingState.h"
#include "../Utilities/Joystick.h"

USING_NS_CC;
class Player : public cocos2d::Node
{
public:
	static Player* createPlayer();
	virtual bool init();
	enum class PlayerState {
		IDLE,
		IDLE_LEFT,
		MOVE_LEFT,
		MOVE_RIGHT,
		JUMPING
	};
	void update(float dt, float leftBorder, float rightBorder);
	void changeState(PlayerState newState);
	Sprite* getSprite() const { return characterSprite; };
	void setDirection(Vec2 dir) { this->direction = dir; };
	Vec2 getDirection() const { return direction; };
	void setJump(bool isJump) { this->isJumping = isJump; };
private:
	MovementState* currentState = nullptr;
	IdleState* idleState;
	IdleLeftState* idleLeftState;
	MoveLeftState* moveLeftState;
	MoveRightState* moveRightState;
	Joystick* _joystick;
	//JumpingState *jumpingState;
	Sprite* characterSprite;
	Vec2 direction = Vec2::ZERO;
	float movementSpeed = 5.0f;
	bool isJumping = false;
};

#endif // !__PLAYER__