#ifndef __PLAYER__
#define __PLAYER__

#include "cocos2d.h"
#include "../State/IdleState.h"
#include "../State/IdleLeftState.h"
#include "../State/MoveLeftState.h"
#include "../State/MoveRightState.h"
#include "../State/JumpingState.h"
#include "../Utilities/Joystick.h"
#include "../Skill/X2Jump.h"

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
	void setJump(bool isTrue) { isJumping = isTrue; };
	void increaseJumpCount() { jumpCount++; };
	bool isX2Coin() const { return x2Coin; };
	void setX2Coin(bool isTrue) { x2Coin = isTrue; };
	void setMaxJumpCount(int value) { maxJumpCount = value; };
	int getMaxJumpCount() { return maxJumpCount; };
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	Sprite* getWingSprite() const { return wingSprite; };
private:
	X2JumpSkill *x2JumpSkill;
	bool x2Coin = false;
	MovementState* currentState = nullptr;
	IdleState* idleState;
	IdleLeftState* idleLeftState;
	MoveLeftState* moveLeftState;
	MoveRightState* moveRightState;
	Joystick* _joystick;
	Sprite* wingSprite;
	//JumpingState *jumpingState;
	Sprite* characterSprite;
	Vec2 direction = Vec2::ZERO;
	float movementSpeed = 5.0f;
	bool isJumping = false;
	int jumpCount = 0;
	float jumpHeight = 30.0f;
	int maxJumpCount = 1;
};

#endif // !__PLAYER__