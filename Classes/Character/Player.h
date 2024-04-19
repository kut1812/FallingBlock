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
#include "../Skill/Shield.h"
#include "../Skill/X2Coin.h"
#include "AudioEngine/AudioEngine.h"
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
	Sprite* getShieldSprite() const { return shieldSprite; };
	bool isInvincible() const { return usingShield; };
	void setInvincible(bool isTrue) { usingShield = isTrue; };
	X2JumpSkill* getX2Jump() const { return this->x2JumpSkill; };
	X2CoinSkill* getX2Coin() const { return this->x2CoinSkill; };
	ShieldSkill* getShield() const { return this->shieldSkill; };
	MovementState* currentState = nullptr;
	bool isCanMove() const { return _isCanMove; };
	void setIsCanMove(bool isTrue) { _isCanMove = isTrue; };
	Vec2 getPrevDir() const { return prevDirection; };
	int getMoney()  { return money; };
	void increaseMoney(int amount) { money += amount; };
	void decreaseMoney(int amount) { money -= amount; };
	void setSkillDuration(float newTime) { skillDuration = newTime; };
	float getSkillDuration() { return skillDuration; };
	int getSkillDurationLevel() { return skillDurationLevel; };
	int getLifeSpawnLevel() { return lifeSpawnLevel; };
	int getMovementLevel() { return movementLevel; };
	void setSkillDurationLevel(int lv);
	void setLifeSpawnLevel(int lv);
	void setMovementLevel(int lv);
	void setSkillShield(ShieldSkill* newSkill) { this->shieldSkill = newSkill; };
	void setSkillJump(X2JumpSkill* newSkill) { this->x2JumpSkill = newSkill; };
	void setSkillCoin(X2CoinSkill* newSkill) { this->x2CoinSkill = newSkill; };
	int getSpawnLife() const { return currentSpawnLife; };
	void decreaseSpawnLife() { currentSpawnLife--; }
	void setBlockSpeedLevel(int newlv) { this->blockSpeedLv = newlv; };
	int getBlockSpeedLevel() const { return this->blockSpeedLv; };
	void spawnLife(); 
	void resetSkill() {
		x2CoinSkill = nullptr;
		x2JumpSkill = nullptr;
		shieldSkill = nullptr;
	}
	void increaseJumpAmount(int amt) { jumpAmount += amt; };
	void increaseCoinAmount(int amt) { coinAmount += amt; };
	void increaseShieldAmount(int amt) { shieldAmount += amt; };
	void decreaseJumpAmount(int amt) { jumpAmount -= amt; };
	void decreaseCoinAmount(int amt) { coinAmount -= amt; };
	void decreaseShieldAmount(int amt) { shieldAmount -= amt; };
	int getJumpAmount() { return jumpAmount; };
	int getCoinAmount() { return coinAmount; };
	int getShieldAmount() { return shieldAmount; };
	float getSpawnTime() const { return currentLifeSpawnTime; };


	int money = 0;
	int movementLevel = 0;
	~Player();
private:
	Audio* audioEngine;
	float skillDuration = 1;
	float currentLifeSpawnTime = 50.0f;
	int currentSpawnLife = 2;
	int skillDurationLevel = 0;
	int lifeSpawnLevel = 0;
	int blockSpeedLv = 0;
	int jumpAmount = 0;
	int coinAmount = 0;
	int shieldAmount = 0;
	bool _isCanMove = true;
	bool usingShield = false;
	X2CoinSkill* x2CoinSkill = nullptr;
	X2JumpSkill* x2JumpSkill = nullptr;
	ShieldSkill* shieldSkill = nullptr;
	bool x2Coin = false;
	IdleState* idleState;
	IdleLeftState* idleLeftState;
	MoveLeftState* moveLeftState;
	MoveRightState* moveRightState;
	Joystick* _joystick;
	Sprite* wingSprite;
	Sprite* shieldSprite;
	//JumpingState *jumpingState;
	Sprite* characterSprite;
	Vec2 direction = Vec2::ZERO;
	float movementSpeed = 200.0f;
	bool isJumping = false;
	int jumpCount = 0;
	float jumpHeight = 30.0f;
	int maxJumpCount = 1;
	cocos2d::Node* playerHead;
	cocos2d::Node* playerHand;
	cocos2d::Node* playerRightHand;
	Vec2 prevDirection = Vec2(0,0);
};

#endif // !__PLAYER__